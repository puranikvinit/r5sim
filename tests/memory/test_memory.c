#include "memory/memory.h"
#include "memory/load_store.h"
#include <stdio.h>
#include <assert.h>

void mem_print(addr_t start_addr,addr_t end_addr,int incr, memory* my_memory){
    if (incr == 1) {
        printf("\nMemory Layout (byte) .....\n");
        for (addr_t addr = start_addr; addr < end_addr; addr += incr) {
            print_mem_byte(my_memory, addr);
        }
    }
    else if (incr == 2) {
        printf("\nMemory Layout (halfword) .....\n");
        for (addr_t addr = start_addr; addr < end_addr; addr += incr) {
            print_mem_half(my_memory, addr);
        }
    }
    else if (incr == 4) {
        printf("\nMemory Layout (word) .....\n");
        for (addr_t addr = start_addr; addr < end_addr; addr += incr) {
            print_mem_word(my_memory, addr);
        }
    }
    else {
        printf("Invalid increment size\n");
    }
    
    printf("........ \n");
}

void mem_inspect() {
    printf("\n=== Memory Inspection ===\n");
    memory *my_memory = get_memory();
    mem_print(0x10000000, 0x10000020, 4, my_memory);

    // Store word
    store_word(my_memory, 0x10000000, 0x12345678);
    store_word(my_memory, 0x10000004, 0x87654321);
    store_word(my_memory, 0x10000008, 0x00000000);
    store_word(my_memory, 0x1000000C, 0xFFFFFFFF);
    
    // Load byte
    reg_t result;
    mem_access_status status = load_word(my_memory, 0x10000000, &result);
    assert(status == MEM_ACCESS_OK);
    assert(result == 0x12345678);
}

int main() {
    // Run all tests
    mem_inspect();
    
    free_memory();
    printf("\nAll tests completed successfully!\n");
    return 0;
}