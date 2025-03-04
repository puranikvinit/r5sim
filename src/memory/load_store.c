#include "memory/load_store.h"

// Memory access check function
mem_access_status check_mem_access(addr_t addr, int size) {
  // Check if address is in valid range
  if (addr < DRAM_START_ADDRESS || addr >= DRAM_END_ADDRESS) {
    return MEM_ACCESS_OUT_OF_BOUNDS;
  }

  // Check if the access spans beyond memory bounds
  if (addr + size - 1 >= DRAM_END_ADDRESS) {
    return MEM_ACCESS_OUT_OF_BOUNDS;
  }

  // Check alignment (RISC-V allows unaligned access, but we'll flag it anyway)
  if (size > 1 && (addr % size != 0)) {
    return MEM_ACCESS_MISALIGNED;
  }

  return MEM_ACCESS_OK;
}

// Load byte (signed)
mem_access_status load_byte(memory *mem, addr_t addr, reg_t *result) {
  // Check memory access validity
  mem_access_status status = check_mem_access(addr, 1);
  if (status != MEM_ACCESS_OK) {
    printf("Error: Invalid memory access at address 0x%08x (load byte)\n",
           addr);
    *result = 0; // Set default value on error
    return status;
  }

  // Read a single byte from memory
  data_t byte = mem_read(mem, addr) & 0xFF;
  // Sign-extend from 8 bits to 32 bits
  *result = (byte & 0x80) ? (byte | 0xFFFFFF00) : byte;
  return MEM_ACCESS_OK;
}

// Load halfword (signed)
mem_access_status load_halfword(memory *mem, addr_t addr, reg_t *result) {
  // Check memory access validity
  mem_access_status status = check_mem_access(addr, 2);
  if (status != MEM_ACCESS_OK) {
    printf("Error: Invalid memory access at address 0x%08x (load halfword)\n",
           addr);
    *result = 0; // Set default value on error
    return status;
  }

  // Read two consecutive bytes and combine them (little-endian)
  data_t low_byte = mem_read(mem, addr) & 0xFF;
  data_t high_byte = mem_read(mem, addr + 1) & 0xFF;
  data_t halfword = (high_byte << 8) | low_byte;
  // Sign-extend from 16 bits to 32 bits
  *result = (halfword & 0x8000) ? (halfword | 0xFFFF0000) : halfword;
  return MEM_ACCESS_OK;
}

// Load word
mem_access_status load_word(memory *mem, addr_t addr, reg_t *result) {
  // Check memory access validity
  mem_access_status status = check_mem_access(addr, 4);
  if (status != MEM_ACCESS_OK) {
    printf("Error: Invalid memory access at address 0x%08x (load word)\n",
           addr);
    *result = 0; // Set default value on error
    return status;
  }

  // Read four consecutive bytes and combine them (little-endian)
  data_t byte0 = mem_read(mem, addr) & 0xFF;
  data_t byte1 = mem_read(mem, addr + 1) & 0xFF;
  data_t byte2 = mem_read(mem, addr + 2) & 0xFF;
  data_t byte3 = mem_read(mem, addr + 3) & 0xFF;
  *result = (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
  return MEM_ACCESS_OK;
}

// Load byte unsigned
mem_access_status load_byte_unsigned(memory *mem, addr_t addr, reg_t *result) {
  // Check memory access validity
  mem_access_status status = check_mem_access(addr, 1);
  if (status != MEM_ACCESS_OK) {
    printf(
        "Error: Invalid memory access at address 0x%08x (load byte unsigned)\n",
        addr);
    *result = 0; // Set default value on error
    return status;
  }

  // Read a single byte and zero-extend (by masking to 8 bits)
  *result = mem_read(mem, addr) & 0xFF;
  return MEM_ACCESS_OK;
}

// Load halfword unsigned
mem_access_status load_halfword_unsigned(memory *mem, addr_t addr,
                                         reg_t *result) {
  // Check memory access validity
  mem_access_status status = check_mem_access(addr, 2);
  if (status != MEM_ACCESS_OK) {
    printf("Error: Invalid memory access at address 0x%08x (load halfword "
           "unsigned)\n",
           addr);
    *result = 0; // Set default value on error
    return status;
  }

  // Read two consecutive bytes and combine them (little-endian)
  data_t low_byte = mem_read(mem, addr) & 0xFF;
  data_t high_byte = mem_read(mem, addr + 1) & 0xFF;
  // Zero-extend (implicit with the way we're combining bytes)
  *result = (high_byte << 8) | low_byte;
  return MEM_ACCESS_OK;
}

// Store byte
mem_access_status store_byte(memory *mem, addr_t addr, reg_t value) {
  // Check memory access validity
  mem_access_status status = check_mem_access(addr, 1);
  if (status != MEM_ACCESS_OK) {
    printf("Error: Invalid memory access at address 0x%08x (store byte)\n",
           addr);
    return status;
  }

  // Store just the lowest byte
  mem_write(mem, addr, value & 0xFF);
  return MEM_ACCESS_OK;
}

// Store halfword
mem_access_status store_halfword(memory *mem, addr_t addr, reg_t value) {
  // Check memory access validity
  mem_access_status status = check_mem_access(addr, 2);
  if (status != MEM_ACCESS_OK) {
    printf("Error: Invalid memory access at address 0x%08x (store halfword)\n",
           addr);
    return status;
  }

  // Store as two separate bytes (little-endian)
  mem_write(mem, addr, value & 0xFF);
  mem_write(mem, addr + 1, (value >> 8) & 0xFF);
  return MEM_ACCESS_OK;
}

// Store word
mem_access_status store_word(memory *mem, addr_t addr, reg_t value) {
  // Check memory access validity
  mem_access_status status = check_mem_access(addr, 4);
  if (status != MEM_ACCESS_OK) {
    printf("Error: Invalid memory access at address 0x%08x (store word)\n",
           addr);
    return status;
  }

  // Store as four separate bytes (little-endian)
  mem_write(mem, addr, value & 0xFF);
  mem_write(mem, addr + 1, (value >> 8) & 0xFF);
  mem_write(mem, addr + 2, (value >> 16) & 0xFF);
  mem_write(mem, addr + 3, (value >> 24) & 0xFF);
  return MEM_ACCESS_OK;
}
