#include "memory/memory.h"
#include "utils/elf_parser.h"

static memory *mem = NULL;

data_t mem_read(memory *mem, addr_t addr) {
  if (addr >= DRAM_START_ADDRESS && addr < DRAM_END_ADDRESS) {
    size_t index = addr - DRAM_START_ADDRESS;
    return mem[index]->data;
  }
  return 0;
}

void mem_write(memory *mem, addr_t addr, data_t data) {
  if (addr >= DRAM_START_ADDRESS && addr < DRAM_END_ADDRESS) {
    size_t index = addr - DRAM_START_ADDRESS;
    mem[index]->data = data;
  }
}

void print_mem_byte(memory *mem, addr_t addr) {
  if (addr >= DRAM_START_ADDRESS && addr < DRAM_END_ADDRESS) {
    size_t index = addr - DRAM_START_ADDRESS;
    printf("0x%08x: 0x%08x\n", addr, mem[index]->data);
  }
}

void print_mem_half(memory *mem, addr_t addr) {
  if (addr >= DRAM_START_ADDRESS && addr < DRAM_END_ADDRESS) {
    size_t index = addr - DRAM_START_ADDRESS;
    printf("0x%08x: 0x%04x%04x\n", addr, mem[index]->data,
           mem[index + 1]->data);
  }
}

void print_mem_word(memory *mem, addr_t addr) {
  if (addr >= DRAM_START_ADDRESS && addr < DRAM_END_ADDRESS) {
    size_t index = addr - DRAM_START_ADDRESS;
    printf("0x%08x: 0x%02x%02x%02x%02x\n", addr, mem[index]->data,
           mem[index + 1]->data, mem[index + 2]->data, mem[index + 3]->data);
  }
}

void mem_clear(memory *mem) {
  for (size_t i = 0; i < DRAM_SIZE; i++) {
    mem[i]->data = 0;
    mem[i]->addr = DRAM_START_ADDRESS + i;
  }
}

void free_memory() {
  if (mem != NULL) {
    free(mem);
    mem = NULL;
  }
}

int mem_init() {
  if (mem == NULL) {
    mem = (memory *)malloc(sizeof(memory));
    mem_clear(mem);
  }

  // LOAD INSTRUCTIONS INTO MEMORY
  FILE *instr_file = fopen(OUTPUT_FILE_PATH, "r");
  if (!instr_file) {
    perror("Failed to open instructions file");
    return 1;
  }

  int num_instr = 0;
  // while (num_instr < MAX_INSTR_NUM &&
  //        fscanf(instr_file, "0x%lx: 0x%x", ,
  //               &entries[count].data) == 2) {
  //   count++;
  // }
}
