#include "cpu/core/registers.h"
#include "config_defines.h"

void reg_file_init(register_file *reg_file) {
  reg_file->x0 = 0;
  for (int i = 0; i < NUM_REGISTERS - 2; i++)
    reg_file->x_gpr[i] = 0;
  reg_file->pc = INSTR_START_ADDRESS;
}

reg_t reg_file_read(register_file *reg_file, int reg_num) {
  switch (reg_num) {
  case 1 ... 31:
    return reg_file->x_gpr[reg_num - 1];
  default:
    printf("registers: invalid register number referenced\n");
  }
  return 0xF0F0F0F0;
}

int reg_file_write(register_file *reg_file, int reg_num, reg_t value) {
  switch (reg_num) {
  case 1 ... 31:
    reg_file->x_gpr[reg_num - 1] = value;
    return 0;
  default:
    printf("registers: invalid register number referenced\n");
  }
  printf("registers: register write operation failed\n");
  return 1;
}

void reg_file_print(register_file *reg_file) {
  printf("registers: x0 -> %u\n", reg_file->x0);
  for (int i = 0; i < NUM_REGISTERS - 2; i++)
    printf("registers: x0 -> %u\n", reg_file->x_gpr[i]);
  printf("registers: pc -> %u\n", reg_file->pc);
}

void reg_file_clear(register_file *reg_file) {
  for (int i = 0; i < NUM_REGISTERS - 2; i++)
    reg_file->x_gpr[i] = 0;
}

reg_t get_pc_value(register_file *reg_file) { return reg_file->pc; }

int set_pc_value(register_file *reg_file, reg_t value) {
  if ((reg_file->pc = value))
    return 0;
  return 1;
}
