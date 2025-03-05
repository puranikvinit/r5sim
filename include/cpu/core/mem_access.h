#ifndef MEM_ACCESS_H
#define MEM_ACCESS_H

#include "cpu/core/instr_decode.h"
#include "cpu/core/instr_exec.h"
#include "memory/memory.h"
#include "registers.h"

typedef struct {
  instr_name instruction_name;
  uint8_t rd;
  reg_t write_data;
  reg_t updated_pc;
} write_back_data;

write_back_data mem_transaction(mem_data exec_mem_data, memory *mem);

#endif // !MEM_ACCESS_H
