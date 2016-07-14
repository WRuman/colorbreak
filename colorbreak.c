/*
 * colorbreak.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <sys/timeb.h>
#include "termctl.h"


//static const char* moveHome = "\x1b[H";
static const char* clearLine = "\x1b[2K";
struct screen screenInfo;

void greet(int x) {
	printf(clearLine);
	moveTo(x, 35);
	printf("Hello World!");
}

void put(char** buff, int y, int x, char item) {
	int offset = y * screenInfo.width + x;
	char* location = (char*)(*buff + (offset * sizeof(char)));
	*location = item;
}

int main(int argc, char **argv)
{
	setupScreen();
	screenInfo = getScreen();
	int buffSize = (screenInfo.height * screenInfo.width + 1) * sizeof(char);
	char* buffer = malloc(buffSize);
	memset(buffer, ' ', buffSize - 1);
	buffer[buffSize - 1] = '\0';
	put(&buffer, 5, 5, 'W');
	put(&buffer, 1, 0, 'R');
	put(&buffer, 23, 79, 'F');
    write(STDOUT_FILENO, buffer, buffSize);
	teardownScreen();
	return 0;
}
