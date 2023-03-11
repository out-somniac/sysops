CC = gcc
CFLAGS = -Wall -Wpedantic -Werror
SOURCES = $(wildcard *.c)
INCLUDE_PATH = includes
TARGET = reverse
TEST_OUT = pomiar_zad_2.txt 

all: BUFFER_SIZE = 1024
all: compile

.PHONY: clean test

compile:
	$(CC) $(CFLAGS) $(SOURCES) -I $(INCLUDE_PATH) -o $(TARGET) -D BUFFER_SIZE=$(BUFFER_SIZE)

test: 
	base64 /dev/urandom  2>/dev/null | head -c 1000 > test.in 
	echo "BufferSize TimeInSeconds" > $(TEST_OUT)
	make compile BUFFER_SIZE=1
	./$(TARGET) test.in test.out >> $(TEST_OUT)
	make compile BUFFER_SIZE=1024
	./$(TARGET) test.in test.out >> $(TEST_OUT)

clean:
	rm -rf *.o *.in *.out $(TARGET) $(TEST_OUT)

.SILENT: