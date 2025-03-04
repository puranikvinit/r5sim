#ifndef LOAD_STORE_H
#define LOAD_STORE_H

#include <stdint.h>

#include "cpu/core/registers.h"
#include "memory/memory.h"

// Memory access exception handling
typedef enum {
  MEM_ACCESS_OK,
  MEM_ACCESS_MISALIGNED,
  MEM_ACCESS_OUT_OF_BOUNDS
} mem_access_status;

// Function to check memory access validity
mem_access_status check_mem_access(addr_t addr, int size);

// Load operations - now return status and store value in pointer
// Load byte (signed) - lb instruction
mem_access_status load_byte(memory *mem, addr_t addr, reg_t *result);
// Load halfword (signed) - lh instruction
mem_access_status load_halfword(memory *mem, addr_t addr, reg_t *result);
// Load word - lw instruction
mem_access_status load_word(memory *mem, addr_t addr, reg_t *result);
// Load byte unsigned - lbu instruction
mem_access_status load_byte_unsigned(memory *mem, addr_t addr, reg_t *result);
// Load halfword unsigned - lhu instruction
mem_access_status load_halfword_unsigned(memory *mem, addr_t addr,
                                         reg_t *result);

// Store operations - now return status
// Store byte - sb instruction
mem_access_status store_byte(memory *mem, addr_t addr, reg_t value);
// Store halfword - sh instruction
mem_access_status store_halfword(memory *mem, addr_t addr, reg_t value);
// Store word - sw instruction
mem_access_status store_word(memory *mem, addr_t addr, reg_t value);

#endif // LOAD_STORE_H
