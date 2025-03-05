# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -DOUTPUT_FILE_PATH=\"instructions.txt\" -Wno-type-limits

# Source files
TEST_SRC = test_memory.c
MEMORY_SRC = ../../src/memory/memory.c

# Include directories
INCLUDES = -I. \
          -I../../include

# Executables
TARGET = test_memory

# Default target
all: $(TARGET)

# Compilation rule
$(TARGET): $(TEST_SRC) $(MEMORY_SRC) $(LOAD_STORE_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

# Clean target
clean:
	rm -f $(TARGET) instructions.hex

# compile and run
test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test