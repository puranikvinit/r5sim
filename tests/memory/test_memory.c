#include "memory/memory.h"
#include <stdio.h>

int main() {
    memory *my_memory = get_memory(); // Get the instance
    mem_write(my_memory, 0x10000000, 0x12345678); // Write to memory
    print_mem_cell(my_memory, 0x10000000); // Print the memory cell
    mem_clear(my_memory); // Clear the memory
    free_memory(); // Free the memory
    return 0;
}