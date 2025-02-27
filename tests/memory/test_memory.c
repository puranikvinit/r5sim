#include "memory/memory.h"
#include "memory/load_store.h"
#include <stdio.h>
#include <assert.h>

void test_basic_memory() {
    printf("\n=== Testing Basic Memory Operations ===\n");
    memory *my_memory = get_memory();
    
    // Write and read a value
    mem_write(my_memory, 0x10000000, 0x12345678);
    print_mem_word(my_memory, 0x10000000);  // Changed from print_mem_cell
    
    data_t read_value = mem_read(my_memory, 0x10000000);
    printf("Read value: 0x%08x\n", read_value);
    assert(read_value == 0x12345678);
    
    // Test memory clear
    mem_clear(my_memory);
    read_value = mem_read(my_memory, 0x10000000);
    printf("After clear, read value: 0x%08x\n", read_value);
    assert(read_value == 0);
}

void test_load_store_operations() {
    printf("\n=== Testing Load/Store Operations ===\n");
    memory *my_memory = get_memory();
    mem_clear(my_memory);
    
    // Test byte operations
    printf("-- Byte Operations --\n");
    store_byte(my_memory, 0x10000000, 0xAB);
    reg_t byte_signed = load_byte(my_memory, 0x10000000);
    reg_t byte_unsigned = load_byte_unsigned(my_memory, 0x10000000);
    printf("Stored: 0xAB, Loaded signed: %d (0x%x), unsigned: %u (0x%x)\n", 
           byte_signed, byte_signed, byte_unsigned, byte_unsigned);
    assert((byte_signed & 0xFF) == 0xAB);
    assert(byte_unsigned == 0xAB);
    
    // Test halfword operations
    printf("\n-- Halfword Operations --\n");
    store_halfword(my_memory, 0x10000002, 0xCDEF);
    reg_t hw_signed = load_halfword(my_memory, 0x10000002);
    reg_t hw_unsigned = load_halfword_unsigned(my_memory, 0x10000002);
    printf("Stored: 0xCDEF, Loaded signed: %d (0x%x), unsigned: %u (0x%x)\n", 
           hw_signed, hw_signed, hw_unsigned, hw_unsigned);
    assert((hw_signed & 0xFFFF) == 0xCDEF);
    assert(hw_unsigned == 0xCDEF);
    
    // Test word operations
    printf("\n-- Word Operations --\n");
    store_word(my_memory, 0x10000004, 0x12345678);
    reg_t word = load_word(my_memory, 0x10000004);
    printf("Stored: 0x12345678, Loaded: 0x%x\n", word);
    assert(word == 0x12345678);
    
    // Print memory contents
    printf("\nMemory Contents:\n");
    for (addr_t addr = 0x10000000; addr < 0x10000008; addr += 4) {
        print_mem_word(my_memory, addr);  // Changed from print_mem_cell
    }
}

void test_sign_extension() {
    printf("\n=== Testing Sign Extension ===\n");
    memory *my_memory = get_memory();
    mem_clear(my_memory);
    
    // Test negative byte sign extension
    store_byte(my_memory, 0x10000010, 0x80);  // -128 in two's complement
    reg_t byte_val = load_byte(my_memory, 0x10000010);
    printf("Stored: 0x80 byte, Loaded signed: %d (0x%x)\n", (int32_t)byte_val, byte_val);
    assert((int32_t)byte_val == -128);
    
    // Test negative halfword sign extension
    store_halfword(my_memory, 0x10000012, 0x8000);  // -32768 in two's complement
    reg_t hw_val = load_halfword(my_memory, 0x10000012);
    printf("Stored: 0x8000 halfword, Loaded signed: %d (0x%x)\n", (int32_t)hw_val, hw_val);
    assert((int32_t)hw_val == -32768);
}

void test_memory_access_check() {
    printf("\n=== Testing Memory Access Validation ===\n");
    
    // Valid access
    mem_access_status status = check_mem_access(0x10000100, 4);
    printf("Access at 0x10000100, size 4: %s\n", 
           status == MEM_ACCESS_OK ? "OK" : 
           status == MEM_ACCESS_MISALIGNED ? "MISALIGNED" : "OUT OF BOUNDS");
    assert(status == MEM_ACCESS_OK);
    
    // Misaligned access
    status = check_mem_access(0x10000101, 4);
    printf("Access at 0x10000101, size 4: %s\n", 
           status == MEM_ACCESS_OK ? "OK" : 
           status == MEM_ACCESS_MISALIGNED ? "MISALIGNED" : "OUT OF BOUNDS");
    assert(status == MEM_ACCESS_MISALIGNED);
    
    // Out of bounds access
    status = check_mem_access(0x20000000, 4);
    printf("Access at 0x20000000, size 4: %s\n", 
           status == MEM_ACCESS_OK ? "OK" : 
           status == MEM_ACCESS_MISALIGNED ? "MISALIGNED" : "OUT OF BOUNDS");
    assert(status == MEM_ACCESS_OUT_OF_BOUNDS);
    
    // Access spanning beyond memory bounds
    status = check_mem_access(MEM_END - 2, 4);
    printf("Access at end of memory - 2, size 4: %s\n", 
           status == MEM_ACCESS_OK ? "OK" : 
           status == MEM_ACCESS_MISALIGNED ? "MISALIGNED" : "OUT OF BOUNDS");
    assert(status == MEM_ACCESS_OUT_OF_BOUNDS);
}

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
    store_word(my_memory, 0x10000000, 0x12345678);
    store_word(my_memory, 0x10000004, 0x87654321);
    store_word(my_memory, 0x10000008, 0xABCDEF01);
    store_word(my_memory, 0x1000000C, 0xFEDCBA09);

    mem_print(0x10000000, 0x10000020, 4, my_memory);
    mem_print(0x10000000, 0x10000020, 2, my_memory);
    mem_print(0x10000000, 0x10000020, 1, my_memory);
}

int main() {
    // Run all tests
    test_basic_memory();
    test_load_store_operations();
    test_sign_extension();
    test_memory_access_check();
    mem_inspect();
    
    free_memory();
    printf("\nAll tests completed successfully!\n");
    return 0;
}