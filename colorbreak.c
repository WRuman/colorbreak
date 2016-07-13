/*
 * colorbreak.c
 * 
 * Copyright 2016 will.ruman <will.ruman@penton.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
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
