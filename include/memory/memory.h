#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "config_defines.h"

typedef uint8_t data_t;
typedef uint32_t addr_t;
typedef uint32_t instr_t;

typedef struct {
  data_t data[DRAM_SIZE * 0x100000];
  addr_t addr[DRAM_SIZE * 0x100000];
} memory;

#define DRAM_END_ADDRESS (DRAM_START_ADDRESS + DRAM_SIZE * 0x100000)
#define MAX_INSTR_NUM ((DRAM_END_ADDRESS - INSTR_START_ADDRESS) / 4)

data_t mem_read(memory *mem, addr_t addr);
void mem_write(memory *mem, addr_t addr, data_t data);
void print_mem_byte(memory *mem, addr_t addr);
void print_mem_half(memory *mem, addr_t addr);
void print_mem_word(memory *mem, addr_t addr);
void mem_clear(memory *mem);
void free_memory();

// 0: success
// 1: file open/read failed
int mem_init();

#endif // !MEMORY_H
