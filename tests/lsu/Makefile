# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -Wno-type-limits 

# Source files
TEST_SRC = test_lsu.c
MEMORY_SRC = ../../src/memory/load_store.c ../../src/memory/memory.c

# Include directories
INCLUDES = -I. \
          -I../../include

# Executables
TARGET = test_lsu

# Default target
all: $(TARGET)

# Compilation rule
$(TARGET): $(TEST_SRC) $(MEMORY_SRC) $(LOAD_STORE_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

# Clean target
clean:
	rm -f $(TARGET)

# compile and run
test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test