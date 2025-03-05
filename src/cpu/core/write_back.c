#include "cpu/core/write_back.h"
#include "cpu/core/instr_decode.h"

void write_back(write_back_data wb_data, register_file *reg_file) {
  switch (wb_data.instruction_name) {
  case lui:
  case auipc:
  case lb:
  case lh:
  case lw:
  case lbu:
  case lhu:
  case addi:
  case slti:
  case sltiu:
  case xori:
  case ori:
  case andi:
  case slli:
  case srli:
  case srai:
  case add:
  case sub:
  case sll:
  case slt:
  case sltu:
  case xor:
  case srl:
  case sra:
  case or:
  case and:
    reg_file->x_gpr[wb_data.rd] = wb_data.write_data;
    printf("write_back: register file updated.\n");
    break;

  case jal:
  case jalr:
    reg_file->x_gpr[wb_data.rd] = wb_data.write_data;
    reg_file->pc = wb_data.updated_pc;
    printf("write_back: register file updated.\n");
    printf("write_back: pc updated.\n");
    break;

  case beq:
  case bne:
  case blt:
  case bge:
  case bltu:
  case bgeu:
    reg_file->pc = wb_data.updated_pc;
    printf("write_back: pc updated.\n");
    break;

  default:
    printf("write_back: register file update not required.\n");
    break;
  }
}
