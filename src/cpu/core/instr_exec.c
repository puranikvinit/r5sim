#include "cpu/core/instr_exec.h"

mem_data execute_instr(exec_data dec_exec_data) {
  mem_data exec_mem_data;
  exec_mem_data.instruction_name = dec_exec_data.instruction_name;
  exec_mem_data.rd = dec_exec_data.rd;

  switch (dec_exec_data.instruction_name) {
  case lui:
    printf("instr_exec: lui - no action required\n");
    exec_mem_data.arith_result = (uint32_t)dec_exec_data.sign_ext_imm;
    break;

  case auipc:
    exec_mem_data.arith_result = dec_exec_data.pc + dec_exec_data.sign_ext_imm;
    break;

  case jal:
    exec_mem_data.arith_result = dec_exec_data.pc + 4;
    exec_mem_data.updated_pc = dec_exec_data.pc + dec_exec_data.sign_ext_imm;
    break;

  case jalr:
    exec_mem_data.arith_result = dec_exec_data.pc + 4;
    exec_mem_data.updated_pc =
        dec_exec_data.rs1_data + dec_exec_data.sign_ext_imm;
    break;

  case beq:
    if (dec_exec_data.rs1_data == dec_exec_data.rs2_data)
      exec_mem_data.updated_pc = dec_exec_data.pc + dec_exec_data.sign_ext_imm;
    break;

  case bne:
    if (dec_exec_data.rs1_data != dec_exec_data.rs2_data)
      exec_mem_data.updated_pc = dec_exec_data.pc + dec_exec_data.sign_ext_imm;
    break;

  case blt:
    if ((int32_t)dec_exec_data.rs1_data < (int32_t)dec_exec_data.rs2_data)
      exec_mem_data.updated_pc = dec_exec_data.pc + dec_exec_data.sign_ext_imm;
    break;

  case bge:
    if ((int32_t)dec_exec_data.rs1_data >= (int32_t)dec_exec_data.rs2_data)
      exec_mem_data.updated_pc = dec_exec_data.pc + dec_exec_data.sign_ext_imm;
    break;

  case bltu:
    if (dec_exec_data.rs1_data < dec_exec_data.rs2_data)
      exec_mem_data.updated_pc = dec_exec_data.pc + dec_exec_data.sign_ext_imm;
    break;

  case bgeu:
    if (dec_exec_data.rs1_data >= dec_exec_data.rs2_data)
      exec_mem_data.updated_pc = dec_exec_data.pc + dec_exec_data.sign_ext_imm;
    break;

  case lb ... lhu:
    exec_mem_data.mem_addr =
        dec_exec_data.rs1_data + dec_exec_data.sign_ext_imm;
    break;

  case sb:
    exec_mem_data.mem_addr =
        dec_exec_data.rs1_data + dec_exec_data.sign_ext_imm;
    exec_mem_data.arith_result = (uint8_t)(dec_exec_data.rs2_data & 0xFF);
    break;

  case sh:
    exec_mem_data.mem_addr =
        dec_exec_data.rs1_data + dec_exec_data.sign_ext_imm;
    exec_mem_data.arith_result = (uint16_t)(dec_exec_data.rs2_data & 0xFFFF);
    break;

  case sw:
    exec_mem_data.mem_addr =
        dec_exec_data.rs1_data + dec_exec_data.sign_ext_imm;
    exec_mem_data.arith_result = dec_exec_data.rs2_data;
    break;

  case addi:
    exec_mem_data.arith_result =
        (int32_t)dec_exec_data.rs1_data + dec_exec_data.sign_ext_imm;
    break;

  case slti:
    exec_mem_data.arith_result =
        ((int32_t)dec_exec_data.rs1_data < dec_exec_data.sign_ext_imm) ? 1 : 0;
    break;

  case sltiu:
    exec_mem_data.arith_result =
        (dec_exec_data.rs1_data < (uint32_t)dec_exec_data.sign_ext_imm) ? 1 : 0;
    break;

  case xori:
    exec_mem_data.arith_result =
        dec_exec_data.rs1_data ^ (uint32_t)dec_exec_data.sign_ext_imm;
    break;

  case ori:
    exec_mem_data.arith_result =
        dec_exec_data.rs1_data | (uint32_t)dec_exec_data.sign_ext_imm;
    break;

  case andi:
    exec_mem_data.arith_result =
        dec_exec_data.rs1_data & (uint32_t)dec_exec_data.sign_ext_imm;
    break;

  case slli:
    exec_mem_data.arith_result =
        dec_exec_data.rs1_data << (uint32_t)(dec_exec_data.sign_ext_imm & 0x1F);
    break;

  case srli:
    exec_mem_data.arith_result =
        dec_exec_data.rs1_data >> (uint32_t)(dec_exec_data.sign_ext_imm & 0x1F);
    break;

  case srai:
    exec_mem_data.arith_result =
        (int32_t)(dec_exec_data.rs1_data >>
                  (uint32_t)(dec_exec_data.sign_ext_imm & 0x1F));
    break;

  case add:
    exec_mem_data.arith_result =
        dec_exec_data.rs1_data + dec_exec_data.rs2_data;
    break;

  case sub:
    exec_mem_data.arith_result =
        dec_exec_data.rs1_data - dec_exec_data.rs2_data;
    break;

  case sll:
    exec_mem_data.arith_result = dec_exec_data.rs1_data
                                 << (uint32_t)(dec_exec_data.rs2_data & 0x1F);
    break;

  case slt:
    exec_mem_data.arith_result =
        ((int32_t)dec_exec_data.rs1_data < (int32_t)dec_exec_data.rs2_data) ? 1
                                                                            : 0;
    break;

  case sltu:
    exec_mem_data.arith_result =
        (dec_exec_data.rs1_data < dec_exec_data.rs2_data) ? 1 : 0;
    break;

  case xor:
    exec_mem_data.arith_result =
        dec_exec_data.rs1_data ^ dec_exec_data.rs2_data;
    break;

  case srl:
    exec_mem_data.arith_result =
        dec_exec_data.rs1_data >> (uint32_t)(dec_exec_data.rs2_data & 0x1F);
    break;

  case sra:
    exec_mem_data.arith_result =
        (int32_t)(dec_exec_data.rs1_data >>
                  (uint32_t)(dec_exec_data.rs2_data & 0x1F));
    break;

  case or:
    exec_mem_data.arith_result =
        dec_exec_data.rs1_data | dec_exec_data.rs2_data;
    break;

  case and:
    exec_mem_data.arith_result =
        dec_exec_data.rs1_data & dec_exec_data.rs2_data;
    break;

  case fence:
    printf("instr_exec: fence - no action required\n");
    break;

  case fencei:
    printf("instr_exec: fence.i - no action required\n");
    break;

  default:
    printf("instr_exec: instruction not part of RV32I\n");
    break;
  }

  return exec_mem_data;
}
