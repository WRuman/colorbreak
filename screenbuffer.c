// screenbuffer.c
#include <stdlib.h>
#include <string.h>
#include "screenbuffer.h"

void init_buffer(struct screenbuffer* sb, const struct screen* scr) {
	unsigned int buff_sz = 0;
	buff_sz += SCREENBUFFER_PREFIX_SZ;
	buff_sz += (scr->height * scr->width);
	buff_sz += SCREENBUFFER_SUFFIX_SZ;
	char* buffer = malloc(buff_sz * CELL_SZ);
	memset(buffer, ' ', buff_sz);
	// Hide cursor and go to 0,0 every draw
	memcpy(buffer, "\x1b[?25l\x1b[H", SCREENBUFFER_PREFIX_SZ);
	(*sb).size = buff_sz;
	(*sb).buffer = buffer;
	(*sb).rows = scr->height;
	(*sb).cols = scr->width;
}

void destroy_buffer(struct screenbuffer* sb) {
	free(sb->buffer);
}

void set_cell(struct screenbuffer* sb, int y, int x, char glyph) {
	unsigned int index = (sb->cols * y) + x;
	index *= CELL_SZ;
	index += SCREENBUFFER_PREFIX_SZ;
	(*sb).buffer[index] = glyph;
}

