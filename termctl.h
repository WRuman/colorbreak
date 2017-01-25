// termctrl.h
#ifndef TERMCTL_H
#define TERMCTL_H

#include <termios.h>
#include <stdio.h>
#include <unistd.h>

struct screen {
	int width;
	int height;
};

struct screen getScreen(void);

int getTerminalConfig(struct termios* tconfig);

int setTerminalConfig(struct termios* tconfig); 

int setRawMode(int term);

#endif //TERMCTL_H
