CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
TARGET = colorbreak

all:$(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
clean:
	$(RM) $(TARGET)
