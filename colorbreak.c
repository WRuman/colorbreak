/*
 * colorbreak.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include "termctl.h"
#include <math.h>

struct screen screenInfo;
struct termios oldTermConfig;

const static int BUFF_PREFIX_SZ = 9;
const static int BUFF_ADD_SZ = 10;


struct screenbuffer {
	int size;
	char* buffer;
};

struct ball {
	double x;
	double y;
	double dx;
	double dy;
};

void put(char** buff, int y, int x, char item) {
	// Add ofset for the reset cursor codes at the front of the buffer
	int offset = y * screenInfo.width + x + BUFF_PREFIX_SZ;
	char* location = (char*)(*buff + (offset * sizeof(char)));
	*location = item;
}

void initScreenBuffer(struct screenbuffer* sb) {
	// Add space for command codes at the front of the buffer with 
	// BUFF_OFFSET
	int buffSize = (screenInfo.height * screenInfo.width + BUFF_ADD_SZ) * sizeof(char);
	char* buffer = malloc(buffSize);
	memset(buffer, ' ', buffSize - 1);
	buffer[buffSize - 1] = '\0';
	// remove cursor
	memcpy(buffer, "\x1b[?25l", 6);
	// Go home on each render
	memcpy(buffer + 6, "\x1b[H", 3);
	(*sb).size = buffSize;
	(*sb).buffer = buffer;
}

void destroyScreenBuffer(struct screenbuffer* sb) {
	free(sb->buffer);
}

long getTimeMs() {
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	return (long)ts.tv_sec * 1000 + (ts.tv_nsec / 1000000);
}

void moveBall(struct screenbuffer* sb, long dt) {
	static struct ball ping = {5.0, 5.0, 0.01, 0.01};
	static int lastX = 0;
	static int lastY = 0;
	
	double newX = ping.x + (dt * ping.dx);
	double newY = ping.y + (dt * ping.dy);	
	if(newX > screenInfo.width) {
		newX = screenInfo.width;
		ping.dx = -ping.dx;
	} else if(newX < 0) {
		newX = 0;
		ping.dx = -ping.dx;
	}
	
	if(newY > screenInfo.height) {
		newY = screenInfo.height;
		ping.dy = -ping.dy;
	} else if(newY < 0) {
		newY = 0;
		ping.dy = -ping.dy;
	}
	
	put(&(sb->buffer), lastY, lastX, ' ');	
	
	ping.x = newX;
	ping.y = newY;
	
	lastX = (int)round(newX);
	lastY = (int)round(newY);
	
	put(&(sb->buffer), lastY, lastX, 'X');
}

void loop(struct screenbuffer* sb) {
	long oldtime = getTimeMs();
	long newtime = 0;
	long frametime = 0;
	long surplus = 0;
	long dt = 33; // ms
	while(1) {
		newtime = getTimeMs();
		frametime = newtime - oldtime;
		oldtime = newtime;
		surplus += frametime;
		while(surplus > dt) {
			moveBall(sb, dt);
			surplus -= dt;
		}
		write(STDOUT_FILENO, sb->buffer, sb->size);
	}
}

int main(int argc, char **argv)
{
	screenInfo = getScreen();
	struct screenbuffer sb; 
	initScreenBuffer(&sb);
	if(getTerminalConfig(&oldTermConfig) != 0) {
		exit(-1);
	}
	
	if(setRawMode(STDOUT_FILENO) != 0) {
		exit(-2);
	}
	/**	
	for(int i = 0; i < screenInfo.width; i++) {
		put(&(sb.buffer), 0, i, '=');
		put(&(sb.buffer), 1, i, '=');
	}
	*/
	loop(&sb);
	
	destroyScreenBuffer(&sb);
	return setTerminalConfig(&oldTermConfig);
}
