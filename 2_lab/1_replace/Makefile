CC = gcc
CFLAGS = -Wall -Wpedantic -Werror
SOURCES = $(wildcard src/*.c)
INCLUDE_PATH = includes
BUILD_PATH = build
TEST_PATH = tests
TARGET = replace

all: compile_sys compile_lib
.PHONY: clean

compile_sys: prepare_build
	$(CC) $(CFLAGS) $(SOURCES) -I $(INCLUDE_PATH) -o $(BUILD_PATH)/sys_$(TARGET)

compile_lib: prepare_build 
	$(CC) $(CFLAGS) $(SOURCES) -I $(INCLUDE_PATH) -o $(BUILD_PATH)/lib_$(TARGET) -D USE_LIB


test: compile_sys compile_lib
	mkdir -p $(TEST_PATH)
	awk 'BEGIN { for (i=1; i<=4096; ++i) printf "."}' > $(TEST_PATH)/test.in
	./$(BUILD_PATH)/sys_$(TARGET) . ! $(TEST_PATH)/test.in $(TEST_PATH)/test.out
	tr . ! < $(TEST_PATH)/test.in > $(TEST_PATH)/tmp
	diff -s $(TEST_PATH)/tmp $(TEST_PATH)/test.out > $(TEST_PATH)/result.txt
	rm -f $(TEST_PATH)/tmp

prepare_build:
	mkdir -p $(BUILD_PATH)

clean:
	rm -rf *.o $(BUILD_PATH) $(TEST_PATH)

.SILENT: