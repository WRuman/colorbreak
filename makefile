CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
TARGET = breakout

all:$(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
clean:
	$(RM) $(TARGET)
