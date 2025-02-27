#ifndef LOAD_STORE_H
#define LOAD_STORE_H

#include "memory/memory.h"
#include "cpu/core/registers.h"

// Load operations
// Load byte (signed) - lb instruction
reg_t load_byte(memory *mem, addr_t addr);
// Load halfword (signed) - lh instruction
reg_t load_halfword(memory *mem, addr_t addr);
// Load word - lw instruction
reg_t load_word(memory *mem, addr_t addr);
// Load byte unsigned - lbu instruction
reg_t load_byte_unsigned(memory *mem, addr_t addr);
// Load halfword unsigned - lhu instruction
reg_t load_halfword_unsigned(memory *mem, addr_t addr);

// Store operations
// Store byte - sb instruction
void store_byte(memory *mem, addr_t addr, reg_t value);
// Store halfword - sh instruction
void store_halfword(memory *mem, addr_t addr, reg_t value);
// Store word - sw instruction
void store_word(memory *mem, addr_t addr, reg_t value);

// Memory access exception handling
typedef enum {
    MEM_ACCESS_OK,
    MEM_ACCESS_MISALIGNED,
    MEM_ACCESS_OUT_OF_BOUNDS
} mem_access_status;

// Function to check memory access validity
mem_access_status check_mem_access(addr_t addr, int size);

#endif // LOAD_STORE_H