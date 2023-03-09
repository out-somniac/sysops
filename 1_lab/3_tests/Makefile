SHELL := /bin/bash
COMPILER = gcc
CFLAGS = -Wall -Wpedantic
HEADERS = $(wildcard *.h)

LIB_TARGET = libwc
LIB_SOURCES = wcbuffer.c

EXEC_TARGET = main
EXEC_SOURCES = main.c lib_loader.h

all: exec_static exec_shared exec_dynamic report clean
.PHONY: clean test test_optimized report

test_optimized: 
	make test OPT_FLAG="-O"
	make test OPT_FLAG="-O0"
	make test OPT_FLAG="-O1"
	make test OPT_FLAG="-O2"
	make test OPT_FLAG="-O3"
	make test OPT_FLAG="-Os"

exec_static: lib_static
	$(CC) $(CFLAGS) $(OPT_FLAG) $(EXEC_SOURCES) $(LIB_TARGET).a -o $(EXEC_TARGET)_static

exec_shared: lib_shared
	$(CC) $(CFLAGS) $(OPT_FLAG) $(EXEC_SOURCES) $(LIB_TARGET).so -o $(EXEC_TARGET)_shared

exec_dynamic: lib_shared
	$(CC) $(CFLAGS) $(OPT_FLAG) $(EXEC_SOURCES) -D USE_DYNAMIC -o $(EXEC_TARGET)_dynamic

lib_static: $(SOURCES)
	$(CC) $(CFLAGS) $(OPT_FLAG) -c $(LIB_SOURCES)
	ar rcs $(LIB_TARGET).a $(LIB_SOURCES:.c=.o)

lib_shared: $(SOURCES)
	$(CC) $(CFLAGS) $(OPT_FLAG) -c -fPIC $(LIB_SOURCES)
	$(CC) $(CFLAGS) $(OPT_FLAG) -shared -o $(LIB_TARGET).so $(LIB_SOURCES:.c=.o)

clean_tests: 
	rm -rf results/ *.test

clean:
	rm -rf *.a *.so *.o
	rm -rf $(EXEC_TARGET)_static $(EXEC_TARGET)_shared $(EXEC_TARGET)_dynamic 

test: exec_static  exec_shared exec_dynamic
	export LD_LIBRARY_PATH=.
	mkdir -p results/
	./$(EXEC_TARGET)_static  <test.txt> results/results_static$(OPT_FLAG).test
	./$(EXEC_TARGET)_shared  <test.txt> results/results_shared$(OPT_FLAG).test
	./$(EXEC_TARGET)_dynamic <test.txt> results/results_dynamic$(OPT_FLAG).test

report: test_optimized
	./report.sh

.SILENT: