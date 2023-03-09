COMPILER = GCC
CFLAGS = -Wall -Wpedantic -Werror
SOURCES = $(wildcard *.c)
TARGET = libwc

all: lib_static lib_shared
.PHONY: clean

lib_static: $(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES)
	ar rcs $(TARGET).a $(SOURCES:.c=.o)

lib_shared: $(SOURCES)
	$(CC) $(CFLAGS) -c -fPIC $(SOURCES)
	$(CC) $(CFLAGS) -shared -o $(TARGET).so $(SOURCES:.c=.o)

clean:
	rm -rf *.o *.a *.so