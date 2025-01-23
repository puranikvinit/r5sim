#ifndef DECODE_H
#define DECODE_H

#include "registers.h"

typedef struct {
  uint8_t opcode : 7;
  uint8_t rd : 5;
  uint8_t funct3 : 3;
  uint8_t rs1 : 5;
  uint8_t rs2 : 5;
  uint8_t funct7 : 7;
} r_instr;

typedef struct {
  uint8_t opcode : 7;
  uint8_t rd : 5;
  uint8_t funct3 : 3;
  uint8_t rs1 : 5;
} i_instr;

typedef struct {
  uint8_t opcode : 7;
  uint8_t funct3 : 3;
  uint8_t rs1 : 5;
  uint8_t rs2 : 5;
} s_instr;

typedef struct {
  uint8_t opcode : 7;
  uint8_t rd : 5;
} u_instr;

typedef struct {
  uint8_t opcode : 7;
  uint8_t rs1 : 5;
  uint8_t rs2 : 5;
  uint8_t funct3 : 3;
} b_instr;

typedef struct {
  uint8_t opcode : 7;
  uint8_t rd : 5;
} j_instr;

typedef enum {
  r_type,
  i_type,
  s_type,
  u_type,
  b_type,
  j_type,
} instr_type;

typedef enum {
  lui,
  auipc,
  jal,
  jalr,
  beq,
  bne,
  blt,
  bge,
  bltu,
  bgeu,
  lb,
  lh,
  lw,
  lbu,
  lhu,
  sb,
  sh,
  sw,
  addi,
  slti,
  sltiu,
  xori,
  ori,
  andi,
  slli,
  srli,
  srai,
  add,
  sub,
  sll,
  slt,
  sltu,
  xor,
  srl,
  sra,
  or
  ,
      and,
  fence,
  fencei,
  ecall,
  ebreak,
  csrrw,
  csrrs,
  csrrc,
  csrrwi,
  csrrsi,
  csrrci,
} instr_name;

typedef struct {
  instr_type instn_type;
  instr_name instruction;
} decoded_opcode;

typedef struct {
  instr_name instruction_name;
  reg_t rs1_data;
  reg_t rs2_data;
  uint8_t rd;
  uint32_t sign_ext_imm;
  reg_t pc;
} alu_data;

alu_data decode_instr(uint32_t fetched_instr, register_file *reg_file);

uint32_t sign_extend_imm(instr_type instn_type, uint32_t instr);

#endif // !DECODE_H
