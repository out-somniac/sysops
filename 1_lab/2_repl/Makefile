SHELL := /bin/bash
COMPILER = gcc
CFLAGS = -Wall -Wpedantic
HEADERS = $(wildcard *.h)

LIB_TARGET = libwc
LIB_SOURCES = wcbuffer.c

EXEC_TARGET = main
EXEC_SOURCES = main.c lib_loader.h

all: exec_static exec_shared exec_dynamic
.PHONY: clean

exec_static: lib_static
	$(CC) $(FLAGS) $(EXEC_SOURCES) $(LIB_TARGET).a -o $(EXEC_TARGET)_static

exec_shared: lib_shared
	$(CC) $(FLAGS) $(EXEC_SOURCES) $(LIB_TARGET).so -o $(EXEC_TARGET)_shared

exec_dynamic: lib_shared
	$(CC) $(CFLAGS) $(EXEC_SOURCES) -D USE_DYNAMIC -o $(EXEC_TARGET)_dynamic

lib_static: $(SOURCES)
	$(CC) $(CFLAGS) -c $(LIB_SOURCES)
	ar rcs $(LIB_TARGET).a $(LIB_SOURCES:.c=.o)

lib_shared: $(SOURCES)
	$(CC) $(CFLAGS) -c -fPIC $(LIB_SOURCES)
	$(CC) $(CFLAGS) -shared -o $(LIB_TARGET).so $(LIB_SOURCES:.c=.o)

clean:
	rm -rf *.o *.a *.so $(EXEC_TARGET)_static $(EXEC_TARGET)_shared $(EXEC_TARGET)_dynamic