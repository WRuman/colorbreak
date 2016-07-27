/*
 * colorbreak.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/timeb.h>
#include "termctl.h"


//static const char* moveHome = "\x1b[H";
static const char* clearLine = "\x1b[2K";
struct screen screenInfo;
struct termios oldTermConfig;

struct screenbuffer {
	int size;
	char* buffer;
};

void greet(int x) {
	printf(clearLine);
	moveTo(x, 35);
	printf("Hello World!");
}

void put(char** buff, int y, int x, char item) {
	// Add three for the reset cursor code at the front of the buffer
	int offset = y * screenInfo.width + x + 3; 
	char* location = (char*)(*buff + (offset * sizeof(char)));
	*location = item;
}

void initScreenBuffer(struct screenbuffer* sb) {
	// Add four, one for the null terminator and three for the reset cursor
	// code at the front of the buffer
	int buffSize = (screenInfo.height * screenInfo.width + 4) * sizeof(char);
	char* buffer = malloc(buffSize);
	memset(buffer, ' ', buffSize - 1);
	buffer[buffSize - 1] = '\0';
	// Go home on each render
	memcpy(buffer, "\x1b[H", 3);
	(*sb).size = buffSize;
	(*sb).buffer = buffer;
}

int main(int argc, char **argv)
{
	screenInfo = getScreen();
	struct screenbuffer sb; 
	if(tcgetattr(STDOUT_FILENO, &oldTermConfig) != 0) {
		exit(-1);
	}
	if(enterRawMode(STDOUT_FILENO) != 0) {
		exit(-2);
	}
	initScreenBuffer(&sb);
	
	while(1) {	
		for(int i = 0; i < screenInfo.width; i++) {
			put(&(sb.buffer), 0, i, '=');
			put(&(sb.buffer), 1, i, '=');
			put(&(sb.buffer), 1, rand() % (screenInfo.width - 1), 'X');
		}
		write(STDOUT_FILENO, sb.buffer, sb.size);
	}
	
	return tcsetattr(STDOUT_FILENO, TCSAFLUSH, &oldTermConfig);
}
