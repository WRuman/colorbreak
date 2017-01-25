CC = gcc
CFLAGS = -Wall -std=c11 -pedantic -g 
TARGET = colorbreak
ADDONS = termctl.c screenbuffer.c
LINK = -lm

all:$(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(ADDONS) $(LINK)

clean:
	$(RM) $(TARGET)
