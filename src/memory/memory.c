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
    printf("instruction file open failed\n");
    return 1;
  }

  int num_instr = 0;
  instr_t instr;
  addr_t mem_addr;
  while (num_instr < MAX_INSTR_NUM &&
         fscanf(instr_file, "0x%x: 0x%x", &mem_addr, &instr) == 2) {
    mem_write(mem, mem_addr, (instr & 0x000000FF));
    mem_write(mem, mem_addr + 1, (instr & 0x0000FF00) >> 8);
    mem_write(mem, mem_addr + 2, (instr & 0x00FF0000) >> 16);
    mem_write(mem, mem_addr + 3, (instr & 0xFF000000) >> 24);
    num_instr++;
  }

  fclose(instr_file);

  return 0;
}
