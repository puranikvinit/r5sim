#include "memory/load_store.h"
#include <stdint.h>

// Memory access check function
mem_access_status check_mem_access(addr_t addr, int size) {
    // Check if address is in valid range
    if (addr < MEM_START || addr >= MEM_END) {
        return MEM_ACCESS_OUT_OF_BOUNDS;
    }
    
    // Check if the access spans beyond memory bounds
    if (addr + size - 1 >= MEM_END) {
        return MEM_ACCESS_OUT_OF_BOUNDS;
    }
    
    // Check alignment (RISC-V allows unaligned access, but we'll flag it anyway)
    if (size > 1 && (addr % size != 0)) {
        return MEM_ACCESS_MISALIGNED;
    }
    
    return MEM_ACCESS_OK;
}

// Load byte (signed)
reg_t load_byte(memory *mem, addr_t addr) {
    // Read a single byte from memory
    data_t byte = mem_read(mem, addr) & 0xFF;
    // Sign-extend from 8 bits to 32 bits
    return (byte & 0x80) ? (byte | 0xFFFFFF00) : byte;
}

// Load halfword (signed)
reg_t load_halfword(memory *mem, addr_t addr) {
    // Read two consecutive bytes and combine them (little-endian)
    data_t low_byte = mem_read(mem, addr) & 0xFF;
    data_t high_byte = mem_read(mem, addr + 1) & 0xFF;
    data_t halfword = (high_byte << 8) | low_byte;
    // Sign-extend from 16 bits to 32 bits
    return (halfword & 0x8000) ? (halfword | 0xFFFF0000) : halfword;
}

// Load word
reg_t load_word(memory *mem, addr_t addr) {
    // Read four consecutive bytes and combine them (little-endian)
    data_t byte0 = mem_read(mem, addr) & 0xFF;
    data_t byte1 = mem_read(mem, addr + 1) & 0xFF;
    data_t byte2 = mem_read(mem, addr + 2) & 0xFF;
    data_t byte3 = mem_read(mem, addr + 3) & 0xFF;
    return (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
}

// Load byte unsigned
reg_t load_byte_unsigned(memory *mem, addr_t addr) {
    // Read a single byte and zero-extend (by masking to 8 bits)
    return mem_read(mem, addr) & 0xFF;
}

// Load halfword unsigned
reg_t load_halfword_unsigned(memory *mem, addr_t addr) {
    // Read two consecutive bytes and combine them (little-endian)
    data_t low_byte = mem_read(mem, addr) & 0xFF;
    data_t high_byte = mem_read(mem, addr + 1) & 0xFF;
    // Zero-extend (implicit with the way we're combining bytes)
    return (high_byte << 8) | low_byte;
}

// Store byte
void store_byte(memory *mem, addr_t addr, reg_t value) {
    // Store just the lowest byte
    mem_write(mem, addr, value & 0xFF);
}

// Store halfword
void store_halfword(memory *mem, addr_t addr, reg_t value) {
    // Store as two separate bytes (little-endian)
    mem_write(mem, addr, value & 0xFF);
    mem_write(mem, addr + 1, (value >> 8) & 0xFF);
}

// Store word
void store_word(memory *mem, addr_t addr, reg_t value) {
    // Store as four separate bytes (little-endian)
    mem_write(mem, addr, value & 0xFF);
    mem_write(mem, addr + 1, (value >> 8) & 0xFF);
    mem_write(mem, addr + 2, (value >> 16) & 0xFF);
    mem_write(mem, addr + 3, (value >> 24) & 0xFF);
}