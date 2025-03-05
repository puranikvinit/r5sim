#include "cpu/core/mem_access.h"
#include "memory/load_store.h"

extern memory *mem;

write_back_data memory_transaction(mem_data exec_mem_data, memory *mem) {
  write_back_data wb_data;
  wb_data.instruction_name = exec_mem_data.instruction_name;
  wb_data.rd = exec_mem_data.rd;
  wb_data.updated_pc = exec_mem_data.updated_pc;
  wb_data.write_data = 0;

  switch (exec_mem_data.instruction_name) {
  case lb:
    switch (
        load_byte(mem, (addr_t)exec_mem_data.mem_addr, &(wb_data.write_data))) {
    case MEM_ACCESS_OK:
      printf("mem_access: loaded byte from memory\n");
      break;

    case MEM_ACCESS_MISALIGNED:
      printf("mem_access: misaligned memory access\n");
      break;

    case MEM_ACCESS_OUT_OF_BOUNDS:
      printf("mem_access: out of bounds memory access\n");
      break;

    default:
      break;
    }
    break;

  case lh:
    switch (load_halfword(mem, (addr_t)exec_mem_data.mem_addr,
                          &(wb_data.write_data))) {
    case MEM_ACCESS_OK:
      printf("mem_access: loaded halfword from memory\n");
      break;

    case MEM_ACCESS_MISALIGNED:
      printf("mem_access: misaligned memory access\n");
      break;

    case MEM_ACCESS_OUT_OF_BOUNDS:
      printf("mem_access: out of bounds memory access\n");
      break;

    default:
      break;
    }
    break;

  case lw:
    switch (
        load_word(mem, (addr_t)exec_mem_data.mem_addr, &(wb_data.write_data))) {
    case MEM_ACCESS_OK:
      printf("mem_access: loaded word from memory\n");
      break;

    case MEM_ACCESS_MISALIGNED:
      printf("mem_access: misaligned memory access\n");
      break;

    case MEM_ACCESS_OUT_OF_BOUNDS:
      printf("mem_access: out of bounds memory access\n");
      break;

    default:
      break;
    }
    break;

  case lbu:
    switch (load_byte_unsigned(mem, (addr_t)exec_mem_data.mem_addr,
                               &(wb_data.write_data))) {
    case MEM_ACCESS_OK:
      printf("mem_access: loaded byte unsigned from memory\n");
      break;

    case MEM_ACCESS_MISALIGNED:
      printf("mem_access: misaligned memory access\n");
      break;

    case MEM_ACCESS_OUT_OF_BOUNDS:
      printf("mem_access: out of bounds memory access\n");
      break;

    default:
      break;
    }
    break;

  case lhu:
    switch (load_halfword_unsigned(mem, (addr_t)exec_mem_data.mem_addr,
                                   &(wb_data.write_data))) {
    case MEM_ACCESS_OK:
      printf("mem_access: loaded halfword unsigned from memory\n");
      break;

    case MEM_ACCESS_MISALIGNED:
      printf("mem_access: misaligned memory access\n");
      break;

    case MEM_ACCESS_OUT_OF_BOUNDS:
      printf("mem_access: out of bounds memory access\n");
      break;

    default:
      break;
    }
    break;

  case sb:
    switch (store_byte(mem, (addr_t)exec_mem_data.mem_addr,
                       exec_mem_data.arith_result)) {
    case MEM_ACCESS_OK:
      printf("mem_access: stored byte to memory\n");
      break;

    case MEM_ACCESS_MISALIGNED:
      printf("mem_access: misaligned memory access\n");
      break;

    case MEM_ACCESS_OUT_OF_BOUNDS:
      printf("mem_access: out of bounds memory access\n");
      break;

    default:
      break;
    }
    break;

  case sh:
    switch (store_halfword(mem, (addr_t)exec_mem_data.mem_addr,
                           exec_mem_data.arith_result)) {
    case MEM_ACCESS_OK:
      printf("mem_access: stored halfword to memory\n");
      break;

    case MEM_ACCESS_MISALIGNED:
      printf("mem_access: misaligned memory access\n");
      break;

    case MEM_ACCESS_OUT_OF_BOUNDS:
      printf("mem_access: out of bounds memory access\n");
      break;

    default:
      break;
    }
    break;

  case sw:
    switch (store_word(mem, (addr_t)exec_mem_data.mem_addr,
                       exec_mem_data.arith_result)) {
    case MEM_ACCESS_OK:
      printf("mem_access: stored word to memory\n");
      break;

    case MEM_ACCESS_MISALIGNED:
      printf("mem_access: misaligned memory access\n");
      break;

    case MEM_ACCESS_OUT_OF_BOUNDS:
      printf("mem_access: out of bounds memory access\n");
      break;

    default:
      break;
    }
    break;

  default:
    wb_data.write_data = exec_mem_data.arith_result;
    printf("mem_access: pass through to write_back\n");
    break;
  }

  return wb_data;
}
