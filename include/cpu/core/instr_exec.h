#ifndef EXEC_H
#define EXEC_H

#include "cpu/core/instr_decode.h"

typedef struct {
  instr_name instruction_name;
  uint8_t rd;
  reg_t arith_result;
  reg_t mem_addr;
  reg_t updated_pc;
} mem_data;

mem_data execute_instr(exec_data dec_alu_data);

#endif // !EXEC_H
