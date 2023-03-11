CC = gcc
CFLAGS = -Wall -Wpedantic -Werror
SOUCES = $(wildcard *.c)
TARGET = list

all: compile

compile:
	$(CC) $(CFLAGS) $(SOUCES) -o $(TARGET)

clean:
	rm -rf *.o $(TARGET)