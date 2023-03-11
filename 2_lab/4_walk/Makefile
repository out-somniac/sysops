CC = gcc
CFLAGS = -Wall -Wpedantic -Werror
SOUCES = $(wildcard *.c)
TARGET = walk

all: compile

compile:
	$(CC) $(CFLAGS) $(SOUCES) -o $(TARGET)

clean:
	rm -rf *.o $(TARGET)