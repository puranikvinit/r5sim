#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>
#include <stdio.h>

#define NUM_REGISTERS 32
#define XLEN 32

#if (XLEN == 32)
typedef uint32_t reg_t;
#else
typedef uint64_t reg_t;
#endif

// For RV32I base integer set:
// x0 -> Hard-wired with all bits set to 0
// x1 - x31 -> Can be used as General Purpose Registers
// pc -> Program Counter; stores the address of the current instruction

// As per the standard function calling conventions:
// 1. x1 -> Return address for a function call
// 2. x5 -> Alternate link register
// 3. x2 -> Stack pointer
typedef struct {
  reg_t x0;
  reg_t x_gpr[NUM_REGISTERS - 1];
  reg_t pc;
} register_file;

void reg_file_init(register_file *reg_file);
reg_t reg_file_read(register_file *reg_file, int reg_num);
int reg_file_write(register_file *reg_file, int reg_num, reg_t value);
void reg_file_print(register_file *reg_file);
void reg_file_clear(register_file *reg_file);

reg_t get_pc_value(register_file *reg_file);
int set_pc_value(register_file *reg_file, reg_t value);

#endif // !REGISTERS_H
