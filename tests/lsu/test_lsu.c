#include <stdio.h>
#include <assert.h>
#include "memory/load_store.h"
#include "memory/memory.h"

extern memory *mem;

// Helper function to set up memory with test values
void setup_test_memory() {
    mem_clear(mem);
    
    // Set up some test values in memory
    store_word(mem, DRAM_START_ADDRESS, 0x12345678);
    store_word(mem, DRAM_START_ADDRESS + 4, 0xABCDEF01);
    store_word(mem, DRAM_START_ADDRESS + 8, 0x87654321);
    store_word(mem, DRAM_START_ADDRESS + 12, 0xFEDCBA98);
}

// Test memory access checking
void test_check_mem_access() {
    printf("Testing memory access checking...\n");
    
    // Valid accesses
    assert(check_mem_access(DRAM_START_ADDRESS, 1) == MEM_ACCESS_OK);
    assert(check_mem_access(DRAM_START_ADDRESS, 2) == MEM_ACCESS_OK);
    assert(check_mem_access(DRAM_START_ADDRESS, 4) == MEM_ACCESS_OK);
    
    // Misaligned accesses
    assert(check_mem_access(DRAM_START_ADDRESS + 1, 2) == MEM_ACCESS_MISALIGNED);
    assert(check_mem_access(DRAM_START_ADDRESS + 1, 4) == MEM_ACCESS_MISALIGNED);
    assert(check_mem_access(DRAM_START_ADDRESS + 2, 4) == MEM_ACCESS_MISALIGNED);
    
    // Out of bounds accesses
    addr_t high_addr = DRAM_END_ADDRESS - 2;
    assert(check_mem_access(high_addr, 4) == MEM_ACCESS_OUT_OF_BOUNDS);
    assert(check_mem_access(DRAM_START_ADDRESS - 1, 1) == MEM_ACCESS_OUT_OF_BOUNDS);
    assert(check_mem_access(DRAM_END_ADDRESS, 1) == MEM_ACCESS_OUT_OF_BOUNDS);
    
    printf("Memory access checking tests passed!\n");
}

// Test load byte (signed)
void test_load_byte() {
    printf("Testing load_byte...\n");
    reg_t result;
    
    setup_test_memory();
    
    // Test regular cases
    assert(load_byte(mem, DRAM_START_ADDRESS, &result) == MEM_ACCESS_OK);
    assert(result == 0x78); // Lowest byte of 0x12345678
    
    assert(load_byte(mem, DRAM_START_ADDRESS + 1, &result) == MEM_ACCESS_OK);
    assert(result == 0x56); // Second byte of 0x12345678
    
    // Test sign extension
    assert(load_byte(mem, DRAM_START_ADDRESS + 12, &result) == MEM_ACCESS_OK);
    assert(result == 0xFFFFFF98); // Sign extended from 0x98
    
    // Test error conditions
    assert(load_byte(mem, DRAM_END_ADDRESS, &result) == MEM_ACCESS_OUT_OF_BOUNDS);
    
    printf("load_byte tests passed!\n");
}

// Test load halfword (signed)
void test_load_halfword() {
    printf("Testing load_halfword...\n");
    reg_t result;
    
    setup_test_memory();
    
    // Test regular cases
    assert(load_halfword(mem, DRAM_START_ADDRESS, &result) == MEM_ACCESS_OK);
    assert(result == 0x5678); // Lowest halfword of 0x12345678
    
    assert(load_halfword(mem, DRAM_START_ADDRESS + 2, &result) == MEM_ACCESS_OK);
    assert(result == 0x1234); // Upper halfword of 0x12345678
    
    // Test sign extension
    assert(load_halfword(mem, DRAM_START_ADDRESS + 12, &result) == MEM_ACCESS_OK);
    assert(result == 0xFFFFBA98); // Sign extended from 0xBA98
    
    // Test misaligned access
    assert(load_halfword(mem, DRAM_START_ADDRESS + 1, &result) == MEM_ACCESS_MISALIGNED);
    
    // Test out of bounds
    assert(load_halfword(mem, DRAM_END_ADDRESS - 1, &result) == MEM_ACCESS_OUT_OF_BOUNDS);
    
    printf("load_halfword tests passed!\n");
}

// Test load word
void test_load_word() {
    printf("Testing load_word...\n");
    reg_t result;
    
    setup_test_memory();
    
    // Test regular cases
    assert(load_word(mem, DRAM_START_ADDRESS, &result) == MEM_ACCESS_OK);
    assert(result == 0x12345678);
    
    assert(load_word(mem, DRAM_START_ADDRESS + 4, &result) == MEM_ACCESS_OK);
    assert(result == 0xABCDEF01);
    
    // Test misaligned access
    assert(load_word(mem, DRAM_START_ADDRESS + 1, &result) == MEM_ACCESS_MISALIGNED);
    assert(load_word(mem, DRAM_START_ADDRESS + 2, &result) == MEM_ACCESS_MISALIGNED);
    
    // Test out of bounds
    assert(load_word(mem, DRAM_END_ADDRESS - 3, &result) == MEM_ACCESS_OUT_OF_BOUNDS);
    
    printf("load_word tests passed!\n");
}

// Test load byte unsigned
void test_load_byte_unsigned() {
    printf("Testing load_byte_unsigned...\n");
    reg_t result;
    
    setup_test_memory();
    
    // Test regular cases
    assert(load_byte_unsigned(mem, DRAM_START_ADDRESS, &result) == MEM_ACCESS_OK);
    assert(result == 0x78); // Lowest byte of 0x12345678
    
    // Test no sign extension
    assert(load_byte_unsigned(mem, DRAM_START_ADDRESS + 12, &result) == MEM_ACCESS_OK);
    assert(result == 0x98); // No sign extension, just 0x98
    
    // Test error conditions
    assert(load_byte_unsigned(mem, DRAM_END_ADDRESS, &result) == MEM_ACCESS_OUT_OF_BOUNDS);
    
    printf("load_byte_unsigned tests passed!\n");
}

// Test load halfword unsigned
void test_load_halfword_unsigned() {
    printf("Testing load_halfword_unsigned...\n");
    reg_t result;
    
    setup_test_memory();
    
    // Test regular cases
    assert(load_halfword_unsigned(mem, DRAM_START_ADDRESS, &result) == MEM_ACCESS_OK);
    assert(result == 0x5678); // Lowest halfword of 0x12345678
    
    // Test no sign extension
    assert(load_halfword_unsigned(mem, DRAM_START_ADDRESS + 12, &result) == MEM_ACCESS_OK);
    assert(result == 0xBA98); // No sign extension
    
    // Test misaligned access
    assert(load_halfword_unsigned(mem, DRAM_START_ADDRESS + 1, &result) == MEM_ACCESS_MISALIGNED);
    
    printf("load_halfword_unsigned tests passed!\n");
}

// Test store byte
void test_store_byte() {
    printf("Testing store_byte...\n");
    reg_t result;
    
    setup_test_memory();
    
    // Test store and verify
    assert(store_byte(mem, DRAM_START_ADDRESS + 16, 0xAB) == MEM_ACCESS_OK);
    assert(load_byte_unsigned(mem, DRAM_START_ADDRESS + 16, &result) == MEM_ACCESS_OK);
    assert(result == 0xAB);
    
    // Make sure only one byte was modified
    store_word(mem, DRAM_START_ADDRESS + 20, 0x11223344);
    assert(store_byte(mem, DRAM_START_ADDRESS + 20, 0xAA) == MEM_ACCESS_OK);
    assert(load_word(mem, DRAM_START_ADDRESS + 20, &result) == MEM_ACCESS_OK);
    assert(result == 0x112233AA); // Only lowest byte changed
    
    // Test error conditions
    assert(store_byte(mem, DRAM_END_ADDRESS, 0xFF) == MEM_ACCESS_OUT_OF_BOUNDS);
    
    printf("store_byte tests passed!\n");
}

// Test store halfword
void test_store_halfword() {
    printf("Testing store_halfword...\n");
    reg_t result;
    
    setup_test_memory();
    
    // Test store and verify
    assert(store_halfword(mem, DRAM_START_ADDRESS + 16, 0xABCD) == MEM_ACCESS_OK);
    assert(load_halfword_unsigned(mem, DRAM_START_ADDRESS + 16, &result) == MEM_ACCESS_OK);
    assert(result == 0xABCD);
    
    // Make sure only two bytes were modified
    store_word(mem, DRAM_START_ADDRESS + 20, 0x11223344);
    assert(store_halfword(mem, DRAM_START_ADDRESS + 20, 0xAABB) == MEM_ACCESS_OK);
    assert(load_word(mem, DRAM_START_ADDRESS + 20, &result) == MEM_ACCESS_OK);
    assert(result == 0x1122AABB); // Only lowest halfword changed
    
    // Test misaligned access
    assert(store_halfword(mem, DRAM_START_ADDRESS + 17, 0xABCD) == MEM_ACCESS_MISALIGNED);
    
    printf("store_halfword tests passed!\n");
}

// Test store word
void test_store_word() {
    printf("Testing store_word...\n");
    reg_t result;
    
    setup_test_memory();
    
    // Test store and verify
    assert(store_word(mem, DRAM_START_ADDRESS + 16, 0xABCDEF12) == MEM_ACCESS_OK);
    assert(load_word(mem, DRAM_START_ADDRESS + 16, &result) == MEM_ACCESS_OK);
    assert(result == 0xABCDEF12);
    
    // Test misaligned access
    assert(store_word(mem, DRAM_START_ADDRESS + 17, 0x12345678) == MEM_ACCESS_MISALIGNED);
    assert(store_word(mem, DRAM_START_ADDRESS + 18, 0x12345678) == MEM_ACCESS_MISALIGNED);
    
    // Test out of bounds
    assert(store_word(mem, DRAM_END_ADDRESS - 3, 0xFFFFFFFF) == MEM_ACCESS_OUT_OF_BOUNDS);
    
    printf("store_word tests passed!\n");
}

// Main test function
void test_lsu() {
    printf("\n===== TESTING LOAD/STORE UNIT =====\n");

    // Initialize memory
    mem_init();
    
    // Run individual tests
    test_check_mem_access();
    test_load_byte();
    test_load_halfword();
    test_load_word();
    test_load_byte_unsigned();
    test_load_halfword_unsigned();
    test_store_byte();
    test_store_halfword();
    test_store_word();
    
    printf("===== ALL LSU TESTS PASSED! =====\n\n");
}

int main() {
    test_lsu();
    free_memory();
    return 0;
}

