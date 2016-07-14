/*
 * colorbreak.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

static const char* useAlternateBuffer = "\x1b[?1047h";
//static const char* moveHome = "\x1b[H";
static const char* clearLine = "\x1b[2K";
static const char* hideCursor = "\x1b[?25l";
//static const char* resetAllAttributes = "\x1b[0m";

void initScreen(void) {
	printf(useAlternateBuffer);
	printf(hideCursor);
}

int main(int argc, char **argv)
{
	initScreen();
	int i = 1;
		
	while(1) {
		printf(clearLine);
		printf("\x1b[%d;35HHello World!", i % 30);
		i++;
	}
	return 0;
}
