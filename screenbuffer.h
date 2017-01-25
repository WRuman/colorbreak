// screenbuffer.h
#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

#include "termctl.h"

const static int SCREENBUFFER_PREFIX_SZ = 9; // bytes
const static int CELL_SZ = 1; //bytes
const static int SCREENBUFFER_SUFFIX_SZ = 0; // bytes

struct screenbuffer {
	int size;
	int cols;
	int rows;
	char* buffer;
};

// Allocates required components of the screenbuffer, sets all cells to space chars
void init_buffer(struct screenbuffer* sb, const struct screen* scr);

// Frees allocated screenbuffer memory. The screenbuffer cannot be used after 
// this is called
void destroy_buffer(struct screenbuffer* sb);

// Sets the glyph in a given cell of the screenbuffer
void set_cell(struct screenbuffer* sb, int y, int x, char glyph);

#endif //SCREENBUFFER_H
