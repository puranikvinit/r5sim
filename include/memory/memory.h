#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef uint32_t data_t;
typedef uint32_t addr_t;

typedef struct {
    data_t data;
    addr_t addr;
} memory_cell;

#define MEM_SIZE 1024
#define MEM_START 0x10000000
#define MEM_END 0x10000000 + MEM_SIZE

typedef struct {
    memory_cell mem_array[MEM_SIZE];
} memory;

memory* get_memory();
data_t mem_read(memory *mem, addr_t addr);
void mem_write(memory *mem, addr_t addr, data_t data);
void print_mem_cell(memory *mem, addr_t addr);
void mem_clear(memory *mem);
void free_memory();

#endif // MEMORY_H