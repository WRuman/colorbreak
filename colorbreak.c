/*
 * colorbreak.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/timeb.h>
#include "termctl.h"


//static const char* moveHome = "\x1b[H";
static const char* clearLine = "\x1b[2K";

void greet(int x) {
	printf(clearLine);
	moveTo(x, 35);
	printf("Hello World!");
}

void put(char** buff, int y, int x, char item) {
	char* location = (buff)
}

int main(int argc, char **argv)
{
	setupScreen();
	struct screen s = getScreen();
	int buffSize = (s.height * s.width) * sizeof(char);
	char* buffer = malloc(buffSize);
	int i = 1;
	
	//struct timeb start, end;
	//ftime(&start);
	/**
	while(1) {
		ftime(&end);
		int diff = end.millitm - start.millitm;
		if(diff >= 500) {
			i++;
			greet(i);
			ftime(&start);
		}
	}
	**/
	teardownScreen();
	return 0;
}
