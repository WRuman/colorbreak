/*
 * colorbreak.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include "termctl.h"
#include "screenbuffer.h"
#include <math.h>

struct screen screenInfo;
struct termios oldTermConfig;

const static int DT = 66; // ms

struct ball {
	double x;
	double y;
	double dx;
	double dy;
};

/**
 * Returns millisecond Unix epoch
 */
long getTimeMs() {
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	return (long)ts.tv_sec * 1000 + (ts.tv_nsec / 1000000);
}

void move_ball(struct screenbuffer* sb) {
	static struct ball ping = {5.0, 5.0, 0.01, 0.01};
	static int lastX = 0;
	static int lastY = 0;
	
	double newX = ping.x + (DT * ping.dx);
	double newY = ping.y + (DT * ping.dy);	
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
	
	set_cell(sb, lastY, lastX, ' ');	
	
	ping.x = newX;
	ping.y = newY;
	
	lastX = (int)round(newX);
	lastY = (int)round(newY);
	
	set_cell(sb, lastY, lastX, 'X');
}

void loop(struct screenbuffer* sb) {
	long now = getTimeMs();
	long lasttime = 0;
	long surplus = 0;
	while(1) {
		now = getTimeMs();
		surplus += (now - lasttime);
		lasttime = now;
		while(surplus > DT) {
			move_ball(sb);
			surplus -= DT;
		}
		write(STDOUT_FILENO, sb->buffer, sb->size);
	}
}

void greet(struct screenbuffer* sb) {
	set_cell(sb, 10, 10, '@');
	write(STDOUT_FILENO, sb->buffer, sb->size);
}

int main(int argc, char **argv) {
	screenInfo = getScreen();
	struct screenbuffer sb; 
	init_buffer(&sb, &screenInfo);
	
	if(getTerminalConfig(&oldTermConfig) != 0) {
		exit(-1);
	}
	if(setRawMode(STDOUT_FILENO) != 0) {
		exit(-2);
	}
	greet(&sb);
	//loop(&sb);
	destroy_buffer(&sb);	
	return setTerminalConfig(&oldTermConfig);
}
