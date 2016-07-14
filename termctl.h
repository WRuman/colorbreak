// termctrl.h
#ifndef TERMCTL_H
#define TERMCTL_H

struct screen {
	int width;
	int height;
};

void teardownScreen(void);

void setupScreen(void);

void moveTo(int y, int x);

struct screen getScreen(void);

int useRawMode(void);

#endif //TERMCTL_H
