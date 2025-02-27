# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra

# Source files
TEST_SRC = test_memory.c
MEMORY_SRC = ../../src/memory/memory.c
LOAD_STORE_SRC = ../../src/memory/load_store.c

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
	rm -f $(TARGET)

# complile and run
test: $(TARGET)
	./$(TARGET)

.PHONY: all clean