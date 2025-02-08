#include "memory/memory.h"

static memory *mem = NULL;

memory* get_memory() {
    if (mem == NULL) {
        mem = (memory*)malloc(sizeof(memory));
        mem_clear(mem); // Initialize the memory
    }
    return mem;
}

data_t mem_read(memory *mem, addr_t addr) {
    if (addr >= MEM_START && addr < MEM_END) {
        size_t index = addr - MEM_START;
        return mem->mem_array[index].data;
    }
    return 0;
}

void mem_write(memory *mem, addr_t addr, data_t data) {
    if (addr >= MEM_START && addr < MEM_END) {
        size_t index = addr - MEM_START;
        mem->mem_array[index].data = data;
    }
}

void print_mem_cell(memory *mem, addr_t addr) {
    if (addr >= MEM_START && addr < MEM_END) {
        size_t index = addr - MEM_START;
        printf("0x%08x: 0x%08x\n", addr, mem->mem_array[index].data);
    }
}

void mem_clear(memory *mem) {
    for (size_t i = 0; i < MEM_SIZE; i++) {
        mem->mem_array[i].data = 0;
        mem->mem_array[i].addr = MEM_START + i;
    }
}

void free_memory() {
    if (mem != NULL) {
        free(mem);
        mem = NULL;
    }
}