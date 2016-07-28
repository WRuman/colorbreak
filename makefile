CC = gcc
CFLAGS = -Wall -std=c11 -pedantic -g -lm
TARGET = colorbreak
ADDONS = termctl.c

all:$(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(ADDONS)

clean:
	$(RM) $(TARGET)
