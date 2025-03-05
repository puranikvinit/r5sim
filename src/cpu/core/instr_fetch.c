#include "cpu/core/instr_fetch.h"
#include "memory/load_store.h"

instr_t fetch_instruction(memory *mem, reg_t *pc){
    // Check memory access validity
    mem_access_status status = check_mem_access(*pc, 4);
    if (status != MEM_ACCESS_OK){
        printf("Error: Invalid memory access at address 0x%08x (fetch instruction)\n", *pc);
        return 0;
    }
    else{
        // Read four consecutive bytes and combine them (little-endian)
        data_t byte0 = mem_read(mem, *pc) & 0xFF;
        data_t byte1 = mem_read(mem, *pc + 1) & 0xFF;
        data_t byte2 = mem_read(mem, *pc + 2) & 0xFF;
        data_t byte3 = mem_read(mem, *pc + 3) & 0xFF;
        *pc += 4;
        return (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
    }
}
