#include "cpu/core/instr_decode.h"
#include "cpu/core/registers.h"

void __handle_opcode_000(decoded_opcode *dec_op, uint8_t opcode,
                         uint32_t instr) {
  switch (opcode) {
  case 0b00:
    dec_op->instn_type = i_type;
    switch ((instr >> 12) & 0x7) {
    case 0b000:
      dec_op->instruction = lb;
      break;

    case 0b001:
      dec_op->instruction = lh;
      break;

    case 0b010:
      dec_op->instruction = lw;
      break;

    case 0b100:
      dec_op->instruction = lbu;
      break;

    case 0b101:
      dec_op->instruction = lhu;
      break;

    default:
      printf("instr_decode: incorrect funct3 type for LOAD\n");
      break;
    }
    break;

  case 0b01:
    dec_op->instn_type = s_type;
    switch ((instr >> 12) & 0x7) {
    case 0b000:
      dec_op->instruction = sb;
      break;

    case 0b001:
      dec_op->instruction = sh;
      break;

    case 0b010:
      dec_op->instruction = sw;
      break;

    default:
      printf("instr_decode: incorrect funct3 type for STORE\n");
      break;
    }
    break;

  case 0b10:
    printf("instr_decode: FMA instructions not supported yet!\n");
    break;

  case 0b11:
    dec_op->instn_type = b_type;
    switch ((instr >> 12) & 0x7) {
    case 0b000:
      dec_op->instruction = beq;
      break;

    case 0b001:
      dec_op->instruction = bne;
      break;

    case 0b100:
      dec_op->instruction = blt;
      break;

    case 0b101:
      dec_op->instruction = bge;
      break;

    case 0b110:
      dec_op->instruction = bltu;
      break;

    case 0b111:
      dec_op->instruction = bgeu;
      break;

    default:
      printf("instr_decode: incorrect funct3 type for BRANCH\n");
      break;
    }
    break;

  default:
    printf("instr_decode: opcode format error\n");
    break;
  }
}

void __handle_opcode_001(decoded_opcode *dec_op, uint8_t opcode,
                         uint32_t instr) {
  switch (opcode) {
  case 0b00:
    printf("instr_decode: FP_LOAD instructions not supported yet!\n");
    break;

  case 0b01:
    printf("instr_decode: FP_STORE instructions not supported yet!\n");
    break;

  case 0b10:
    printf("instr_decode: FMA instructions not supported yet!\n");
    break;

  case 0b11:
    dec_op->instn_type = i_type;
    dec_op->instruction = jalr;
    break;

  default:
    printf("instr_decode: opcode format error\n");
    break;
  }
}

void __handle_opcode_010(decoded_opcode *dec_op, uint8_t opcode,
                         uint32_t instr) {
  printf("instr_decode: custom instructions not supported yet!\n");
}

void __handle_opcode_011(decoded_opcode *dec_op, uint8_t opcode,
                         uint32_t instr) {
  switch (opcode) {
  case 0b00:
    dec_op->instn_type = i_type;
    switch ((instr >> 12) & 0x7) {
    case 0b000:
      dec_op->instruction = fence;
      break;

    case 0b001:
      dec_op->instruction = fencei;
      break;

    default:
      printf("instr_decode: incorrect funct3 type for FENCE\n");
      break;
    }
    break;

  case 0b01:
    printf("instr_decode: AMO instruction not supported yet!\n");
    break;

  case 0b10:
    printf("instr_decode: FMA instructions not supported yet!\n");
    break;

  case 0b11:
    dec_op->instn_type = j_type;
    dec_op->instruction = jal;
    break;

  default:
    printf("instr_decode: opcode format error\n");
    break;
  }
}

void __handle_opcode_100(decoded_opcode *dec_op, uint8_t opcode,
                         uint32_t instr) {
  switch (opcode) {
  case 0b00:
    dec_op->instn_type = i_type;
    switch ((instr >> 12) & 0x7) {
    case 0b000:
      dec_op->instruction = addi;
      break;

    case 0b001:
      dec_op->instruction = slli;
      break;

    case 0b010:
      dec_op->instruction = slti;
      break;

    case 0b011:
      dec_op->instruction = sltiu;
      break;

    case 0b100:
      dec_op->instruction = xori;
      break;

    case 0b101:
      switch ((instr >> 25)) {
      case 0b0000000:
        dec_op->instruction = srli;
        break;

      case 0b0100000:
        dec_op->instruction = srai;
        break;

      default:
        printf("instr_decode: incorrect funct7 type for SHIFT_RIGHT\n");
        break;
      }
      break;

    case 0b110:
      dec_op->instruction = ori;
      break;

    case 0b111:
      dec_op->instruction = andi;
      break;

    default:
      printf("instr_decode: incorrect funct3 type for ARITHMETIC\n");
      break;
    }
    break;

  case 0b01:
    dec_op->instn_type = r_type;
    switch ((instr >> 12) & 0x07) {
    case 0b000:
      switch (instr >> 25) {
      case 0b0000000:
        dec_op->instruction = add;
        break;

      case 0b0100000:
        dec_op->instruction = sub;
        break;

      default:
        printf("instr_decode: incorrect funct7 type for ADD");
        break;
      }
      break;

    case 0b001:
      dec_op->instruction = sll;
      break;

    case 0b010:
      dec_op->instruction = slt;
      break;

    case 0b011:
      dec_op->instruction = sltu;
      break;

    case 0b100:
      dec_op->instruction = xor;
      break;

    case 0b101:
      switch (instr >> 25) {
      case 0b0000000:
        dec_op->instruction = srl;
        break;

      case 0b0100000:
        dec_op->instruction = sra;
        break;

      default:
        printf("instr_decode: incorrect funct7 type for SHIFT_RIGHT\n");
        break;
      }
      break;

    case 0b110:
      dec_op->instruction = or ;
      break;

    case 0b111:
      dec_op->instruction = and;
      break;

    default:
      printf("instr_decode: incorrect funct3 type for ARITHMETIC\n");
      break;
    }
    break;

  case 0b10:
    printf("instr_decode: FP instructions not supported yet!\n");
    break;

  case 0b11:
    dec_op->instn_type = i_type;
    switch ((instr >> 12) & 0x07) {
    case 0b000:
      switch (instr >> 24) {
      case 0x0:
        dec_op->instruction = ecall;
        break;

      case 0x1:
        dec_op->instruction = ebreak;
        break;

      default:
        printf("instr_decode: incorrect imm value for ECALL\n");
        break;
      }
      break;

    case 0b001:
      dec_op->instruction = csrrw;
      break;

    case 0b010:
      dec_op->instruction = csrrs;
      break;

    case 0b011:
      dec_op->instruction = csrrc;
      break;

    case 0b101:
      dec_op->instruction = csrrwi;
      break;

    case 0b110:
      dec_op->instruction = csrrsi;
      break;

    case 0b111:
      dec_op->instruction = csrrci;
      break;

    default:
      printf("instr_decode: incorrect funct3 value for CSR\n");
      break;
    }
    break;
  }
}

void __handle_opcode_110(decoded_opcode *dec_op, uint8_t opcode,
                         uint32_t instr) {
  switch (opcode) {
  case 0b00:
    dec_op->instn_type = u_type;
    dec_op->instruction = auipc;
    break;

  case 0b01:
    dec_op->instn_type = u_type;
    dec_op->instruction = lui;
    break;

  default:
    printf("instr_decode: custom RV128 instructions not supported yet!\n");
    break;
  }
}

decoded_opcode __decode_opcode(uint32_t fetched_instr) {
  decoded_opcode dec_op;
  uint8_t opcode = fetched_instr & 0x7F;

  if ((opcode & 0x3) != 0x3) {
    printf("instr_decode: opcode format error\n");
    return (decoded_opcode){};
  }

  opcode >>= 2;

  switch (opcode & 0x7) {
  case 0b000:
    __handle_opcode_000(&dec_op, (opcode >> 0x7), fetched_instr);
    break;

  case 0b001:
    __handle_opcode_001(&dec_op, (opcode >> 0x7), fetched_instr);
    break;

  case 0b010:
    __handle_opcode_010(&dec_op, (opcode >> 0x7), fetched_instr);
    break;

  case 0b011:
    __handle_opcode_011(&dec_op, (opcode >> 0x7), fetched_instr);
    break;

  case 0b100:
    __handle_opcode_100(&dec_op, (opcode >> 0x7), fetched_instr);
    break;

  case 0b110:
    __handle_opcode_110(&dec_op, (opcode >> 0x7), fetched_instr);
    break;

  default:
    printf("instr_decode: opcode format error\n");
    return (decoded_opcode){};
    break;
  }

  return dec_op;
}

alu_data decode_instr(uint32_t fetched_instr, register_file *reg_file) {
  alu_data dec_alu_data;

  decoded_opcode dec_op = __decode_opcode(fetched_instr);
  dec_alu_data.instruction_name = dec_op.instruction;
  dec_alu_data.pc = get_pc_value(reg_file);

  decoded_instr instr = {};
  switch (dec_op.instn_type) {
  case r_type:
    instr.opcode = fetched_instr & 0b1111111;
    instr.rd = (fetched_instr >> 7) & 0b11111;
    instr.funct3 = (fetched_instr >> 12) & 0b111;
    instr.rs1 = (fetched_instr >> 15) & 0b11111;
    instr.rs2 = (fetched_instr >> 20) & 0b11111;
    instr.funct7 = fetched_instr >> 25;

    dec_alu_data.rs1_data = reg_file_read(reg_file, instr.rs1);
    dec_alu_data.rs2_data = reg_file_read(reg_file, instr.rs2);
    dec_alu_data.rd = instr.rd;
    break;

  case i_type:
    instr.opcode = fetched_instr & 0b1111111;
    instr.rd = (fetched_instr >> 7) & 0b11111;
    instr.funct3 = (fetched_instr >> 12) & 0b111;
    instr.rs1 = (fetched_instr >> 15) & 0b11111;

    dec_alu_data.rs1_data = reg_file_read(reg_file, instr.rs1);
    dec_alu_data.rd = instr.rd;
    dec_alu_data.sign_ext_imm =
        sign_extend_imm(dec_op.instn_type, fetched_instr);
    break;

  case s_type:
    instr.opcode = fetched_instr & 0b1111111;
    instr.funct3 = (fetched_instr >> 12) & 0b111;
    instr.rs1 = (fetched_instr >> 15) & 0b11111;
    instr.rs2 = (fetched_instr >> 20) & 0b11111;
    dec_alu_data.rs1_data = reg_file_read(reg_file, instr.rs1);
    dec_alu_data.rs2_data = reg_file_read(reg_file, instr.rs2);
    dec_alu_data.sign_ext_imm =
        sign_extend_imm(dec_op.instn_type, fetched_instr);
    break;

  case u_type:
    instr.opcode = fetched_instr & 0b1111111;
    instr.rd = (fetched_instr >> 7) & 0b11111;
    dec_alu_data.rd = instr.rd;
    dec_alu_data.sign_ext_imm =
        sign_extend_imm(dec_op.instn_type, fetched_instr);
    break;

  case b_type:
    instr.opcode = fetched_instr & 0b1111111;
    instr.funct3 = (fetched_instr >> 12) & 0b111;
    instr.rs1 = (fetched_instr >> 15) & 0b11111;
    instr.rs2 = (fetched_instr >> 20) & 0b11111,
    dec_alu_data.rs1_data = reg_file_read(reg_file, instr.rs1);
    dec_alu_data.rs2_data = reg_file_read(reg_file, instr.rs2);
    dec_alu_data.sign_ext_imm =
        sign_extend_imm(dec_op.instn_type, fetched_instr);
    break;

  case j_type:
    instr.opcode = fetched_instr & 0b1111111;
    instr.rd = (fetched_instr >> 7) & 0b11111;
    dec_alu_data.rd = instr.rd;
    dec_alu_data.sign_ext_imm =
        sign_extend_imm(dec_op.instn_type, fetched_instr);
    break;

  default:
    printf("instr_decode: invalid instruction type\n");
    break;
  }

  return dec_alu_data;
}

uint32_t sign_extend_imm(instr_type instn_type, uint32_t instr) {
  uint32_t sign_ext_imm = (instr >> 31) ? 0xFFFFFFFF : 0;

  switch (instn_type) {
  case r_type:
    printf("instr_decode: imm not allowed in R-instructions\n");
    break;

  case i_type:
    sign_ext_imm <<= 11;
    sign_ext_imm |= (((instr >> 25) & 0b111111) << 5);
    sign_ext_imm |= (((instr >> 21) & 0b1111) << 1);
    sign_ext_imm |= ((instr >> 20) & 0b1);
    break;

  case s_type:
    sign_ext_imm <<= 11;
    sign_ext_imm |= (((instr >> 25) & 0b111111) << 5);
    sign_ext_imm |= (((instr >> 8) & 0b1111) << 1);
    sign_ext_imm |= ((instr >> 7) & 0b1);
    break;

  case u_type:
    sign_ext_imm = (sign_ext_imm << 31);
    sign_ext_imm |= (((instr >> 20) & 0b11111111111) << 20);
    sign_ext_imm |= (((instr >> 12) & 0b11111111) << 12);
    break;

  case b_type:
    sign_ext_imm <<= 12;
    sign_ext_imm |= (((instr >> 7) & 0b1) << 11);
    sign_ext_imm |= (((instr >> 25) & 0b111111) << 5);
    sign_ext_imm |= (((instr >> 8) & 0b1111) << 1);
    break;

  case j_type:
    sign_ext_imm <<= 20;
    sign_ext_imm |= (((instr >> 12) & 0b11111111) << 12);
    sign_ext_imm |= (((instr >> 20) & 0b1) << 11);
    sign_ext_imm |= (((instr >> 25) & 0b111111) << 5);
    sign_ext_imm |= (((instr >> 21) & 0b1111) << 1);
    break;

  default:
    printf("instr_decode: invalid instruction type\n");
    break;
  }

  return sign_ext_imm;
}
