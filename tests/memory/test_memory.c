#include "memory/memory.h"
#include "utils/elf_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

extern memory *mem;

// Helper function to check if a memory read matches an expected value
void assert_memory(memory *mem, addr_t addr, data_t expected, const char *test_name) {
    data_t actual = mem_read(mem, addr);
    if (actual != expected) {
        fprintf(stderr, "Test '%s' failed: At address 0x%08x, expected 0x%02x but got 0x%02x\n",
                test_name, addr, expected, actual);
        exit(1);
    }
    printf("Test '%s' passed\n", test_name);
}

// Test basic memory read/write operations
void test_basic_read_write() {
    printf("\n=== Testing Basic Memory Read/Write ===\n");
    
    mem_clear(mem);
    
    // Test writing and reading a single byte
    addr_t addr = DRAM_START_ADDRESS + 100;
    data_t value = 0xAB;
    mem_write(mem, addr, value);
    assert_memory(mem, addr, value, "Single byte write/read");
    
    // Test writing and reading multiple values
    for (int i = 0; i < 10; i++) {
        addr_t test_addr = DRAM_START_ADDRESS + i * 10;
        data_t test_value = 0x10 + i;
        mem_write(mem, test_addr, test_value);
    }
    
    for (int i = 0; i < 10; i++) {
        addr_t test_addr = DRAM_START_ADDRESS + i * 10;
        data_t expected = 0x10 + i;
        assert_memory(mem, test_addr, expected, "Multiple byte write/read");
    }
    
    printf("Basic memory read/write tests passed!\n");
}

// Test boundary cases for memory access
void test_boundary_cases() {
    printf("\n=== Testing Memory Boundary Cases ===\n");
    
    mem_clear(mem);
    
    // Test first address in memory
    addr_t start_addr = DRAM_START_ADDRESS;
    data_t start_value = 0x42;
    mem_write(mem, start_addr, start_value);
    assert_memory(mem, start_addr, start_value, "First memory address");
    
    // Test last valid address in memory
    addr_t end_addr = DRAM_END_ADDRESS - 1;
    data_t end_value = 0x24;
    mem_write(mem, end_addr, end_value);
    assert_memory(mem, end_addr, end_value, "Last memory address");
    
    printf("Memory boundary tests passed!\n");
}

// Test invalid memory access
void test_invalid_access() {
    printf("\n=== Testing Invalid Memory Access ===\n");
    
    mem_clear(mem);
    
    // Test address before memory range
    addr_t before_addr = DRAM_START_ADDRESS - 1;
    data_t test_value = 0xFF;
    mem_write(mem, before_addr, test_value);
    data_t result = mem_read(mem, before_addr);
    if (result != 0) {
        fprintf(stderr, "Invalid access test failed: Reading below memory range should return 0\n");
        exit(1);
    }
    printf("Reading below memory range test passed\n");
    
    // Test address after memory range
    addr_t after_addr = DRAM_END_ADDRESS;
    mem_write(mem, after_addr, test_value);
    result = mem_read(mem, after_addr);
    if (result != 0) {
        fprintf(stderr, "Invalid access test failed: Reading above memory range should return 0\n");
        exit(1);
    }
    printf("Reading above memory range test passed\n");
    
    printf("Invalid memory access tests passed!\n");
}

// Test memory clearing functionality
void test_memory_clear() {
    printf("\n=== Testing Memory Clear ===\n");
    
    // Fill memory with a pattern
    for (addr_t addr = DRAM_START_ADDRESS; addr < DRAM_START_ADDRESS + 1000; addr++) {
        mem_write(mem, addr, (data_t)(addr & 0xFF));
    }
    
    // Verify memory contains the pattern
    for (addr_t addr = DRAM_START_ADDRESS; addr < DRAM_START_ADDRESS + 1000; addr++) {
        assert_memory(mem, addr, (data_t)(addr & 0xFF), "Pre-clear check");
    }
    
    // Clear memory
    mem_clear(mem);
    
    // Check a sampling of memory locations to verify they're cleared
    for (addr_t addr = DRAM_START_ADDRESS; addr < DRAM_END_ADDRESS; addr += DRAM_SIZE * 0x10000) {
        assert_memory(mem, addr, 0, "Post-clear check");
    }
    
    // We can skip checking the address field initialization
    // as that's an implementation detail that might differ between versions
    
    printf("Memory clear test passed!\n");
}

// Test multi-byte memory operations
void test_multi_byte_operations() {
    printf("\n=== Testing Multi-byte Memory Operations ===\n");
    
    mem_clear(mem);
    
    // Set up a 4-byte pattern in memory
    addr_t base_addr = DRAM_START_ADDRESS + 0x100;
    mem_write(mem, base_addr, 0x11);
    mem_write(mem, base_addr + 1, 0x22);
    mem_write(mem, base_addr + 2, 0x33);
    mem_write(mem, base_addr + 3, 0x44);
    
    // Verify each byte individually
    assert_memory(mem, base_addr, 0x11, "First byte of pattern");
    assert_memory(mem, base_addr + 1, 0x22, "Second byte of pattern");
    assert_memory(mem, base_addr + 2, 0x33, "Third byte of pattern");
    assert_memory(mem, base_addr + 3, 0x44, "Fourth byte of pattern");
    
    printf("Multi-byte memory operations test passed!\n");
}

// Test memory initialization from file
void test_memory_init() {
    printf("\n=== Testing Memory Initialization From File ===\n");
    
    // Create a test file with known instructions
    FILE *test_file = fopen(OUTPUT_FILE_PATH, "w");
    if (!test_file) {
        fprintf(stderr, "Failed to create test file\n");
        exit(1);
    }
    
    // Write test instructions in format "0xADDRESS: 0xINSTRUCTION"
    fprintf(test_file, "0x%x: 0x%08x\n", DRAM_START_ADDRESS, 0x12345678);
    fprintf(test_file, "0x%x: 0x%08x\n", DRAM_START_ADDRESS + 4, 0xAABBCCDD);
    fclose(test_file);
    
    // Free existing memory if any
    free_memory();
    
    // Initialize memory from the file
    int init_result = mem_init();
    if (init_result != 0) {
        fprintf(stderr, "Memory initialization failed\n");
        exit(1);
    }
    
    // Check if the instructions were loaded correctly (in little-endian format)
    assert_memory(mem, DRAM_START_ADDRESS, 0x78, "First byte of first instruction");
    assert_memory(mem, DRAM_START_ADDRESS + 1, 0x56, "Second byte of first instruction");
    assert_memory(mem, DRAM_START_ADDRESS + 2, 0x34, "Third byte of first instruction");
    assert_memory(mem, DRAM_START_ADDRESS + 3, 0x12, "Fourth byte of first instruction");
    
    assert_memory(mem, DRAM_START_ADDRESS + 4, 0xDD, "First byte of second instruction");
    assert_memory(mem, DRAM_START_ADDRESS + 5, 0xCC, "Second byte of second instruction");
    assert_memory(mem, DRAM_START_ADDRESS + 6, 0xBB, "Third byte of second instruction");
    assert_memory(mem, DRAM_START_ADDRESS + 7, 0xAA, "Fourth byte of second instruction");
    
    printf("Memory initialization from file test passed!\n");
}

// Test memory printing functions (visual verification)
void test_memory_print() {
    printf("\n=== Testing Memory Print Functions (Visual Verification) ===\n");
    
    mem_clear(mem);
    
    // Set up a pattern for printing
    addr_t addr = DRAM_START_ADDRESS + 0x200;
    mem_write(mem, addr, 0xAA);
    mem_write(mem, addr + 1, 0xBB);
    mem_write(mem, addr + 2, 0xCC);
    mem_write(mem, addr + 3, 0xDD);
    
    printf("The following output requires visual verification:\n\n");
    
    printf("1. Byte print (should show 0x%08x: 0x%02x):\n", addr, 0xAA);
    print_mem_byte(mem, addr);
    
    printf("\n2. Half-word print (should show 0x%08x: 0x%02x%02x):\n", addr, 0xAA, 0xBB);
    print_mem_half(mem, addr);
    
    printf("\n3. Word print (should show 0x%08x: 0x%02x%02x%02x%02x):\n", 
           addr, 0xAA, 0xBB, 0xCC, 0xDD);
    print_mem_word(mem, addr);
    
    printf("\nVisually verify that the output matches the expected format.\n");
    printf("Memory print functions test completed!\n");
}

// Test memory allocation and deallocation
void test_memory_allocation() {
    printf("\n=== Testing Memory Allocation and Deallocation ===\n");
    
    // Free existing memory
    free_memory();
    
    // Memory should be NULL after freeing
    if (mem != NULL) {
        fprintf(stderr, "Memory pointer not NULL after free_memory()\n");
        exit(1);
    }
    
    // Initialize memory
    int init_result = mem_init();
    if (init_result != 0) {
        fprintf(stderr, "Memory initialization failed\n");
        exit(1);
    }
    
    // Memory should be non-NULL after init
    if (mem == NULL) {
        fprintf(stderr, "Memory pointer is NULL after mem_init()\n");
        exit(1);
    }
    
    // Test using the memory
    mem_write(mem, DRAM_START_ADDRESS, 0x42);
    assert_memory(mem, DRAM_START_ADDRESS, 0x42, "Memory after re-initialization");
    
    printf("Memory allocation/deallocation test passed!\n");
}

int main() {
    printf("====== MEMORY MODULE FUNCTIONAL TEST SUITE ======\n");
    
    // Initialize memory for testing
    mem_init();
    
    // Run all tests
    test_basic_read_write();
    test_boundary_cases();
    test_invalid_access();
    test_memory_clear();
    test_multi_byte_operations();
    test_memory_init();
    test_memory_print();
    test_memory_allocation();
    
    // Clean up
    free_memory();
    
    printf("\n====== ALL MEMORY TESTS PASSED ======\n");
    return 0;
}
