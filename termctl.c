// termctl.c
#include "termctl.h"
#include <stdio.h>
#include <termios.h>

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

/**
 * Code and concepts borrowed from antirez's editor, named "kilo".
 * Roughly equivalent to the function cfmakeraw() in termios.h
 */
int enterRawMode(int term) {
	struct termios termConfig;
	if(tcgetattr(term, &termConfig) != 0) {
		return 1;
	}
	/**
	 * Sets input modes in the terminal configuration
	 * ! BRKINT - BREAK will read as a null byte. Also don't flush io on BREAK
	 * ! ICRNL - Don't translate carriage returns to newlines
	 * ! INPCK - Don't check input parity
	 * ! ISTRIP - Don't strip out 8th bit on input chars
	 * ! IXON - Don't allow xon/xoff signaling to resume and pause activity
	 */
	termConfig.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	// No implementation specific post processing of output
	termConfig.c_oflag &= ~(OPOST);
	// Character size mask set to 8 bits
	termConfig.c_cflag |= (CS8);
	/**
	 * Sets local terminal modes
	 * ! ECHO - Don't echo input characters
	 * ! ICANON - "Non canonical" mode: input available immediately as user 
	 * provides it, line editing is disabled, no special processing of input
	 * or output characters
	 * ! IEXTEN - Disable implementation defined input processing
	 * ! ISIG - Don't generate signal when INTR, QUIT, SUSP, or DSUSP characters
	 * are recieved
	 */
	termConfig.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	termConfig.c_cc[VMIN] = 0; // Min. chars required for a read
	termConfig.c_cc[VTIME] = 1; // Decisecond timeout for input read
	if(tcsetattr(term, TCSAFLUSH, &termConfig) != 0) {
		return 2;
	}
	return 0;
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
