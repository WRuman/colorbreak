CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
TARGET = colorbreak
ADDONS = termctl.c

all:$(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(ADDONS)

clean:
	$(RM) $(TARGET)
