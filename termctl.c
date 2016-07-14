// termctl.c
#include "termctl.h"
#include <stdio.h>

static const char* enterAltBuff = "\x1b[?1047h";
static const char* exitAltBuff = "\x1b[?1047l";
static const char* rmCursor = "\x1b[?25l";
static const char* addCursor = "\x1b[?25h";

void teardownScreen(void) {
	printf(exitAltBuff);
	printf(addCursor);
}

void setupScreen(void) {
	printf(enterAltBuff);
	printf(rmCursor);
}

void moveTo(int y, int x) {
	printf("\x1b[%d;%d", y, x);
}

struct screen getScreen(void) {
	struct screen s;
	s.width = 80;
	s.height = 24;
	return s;
}

int useRawMode(void) {
	return 0;
}
