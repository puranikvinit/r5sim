#include "memory/memory.h"
#include "utils/elf_parser.h"

memory *mem = NULL;

data_t mem_read(memory *mem, addr_t addr) {
  if (addr < DRAM_END_ADDRESS && addr >= DRAM_START_ADDRESS) {
    size_t index = addr - DRAM_START_ADDRESS;
    return mem->data[index];
  }
  return 0;
}

void mem_write(memory *mem, addr_t addr, data_t data) {
  if (addr < DRAM_END_ADDRESS && addr >= DRAM_START_ADDRESS) {
    size_t index = addr - DRAM_START_ADDRESS;
    mem->data[index] = data;
  }
}

void print_mem_byte(memory *mem, addr_t addr) {
  if (addr < DRAM_END_ADDRESS && addr >= DRAM_START_ADDRESS) {
    size_t index = addr - DRAM_START_ADDRESS;
    printf("0x%08x: 0x%08x\n", addr, mem->data[index]);
  }
}

void print_mem_half(memory *mem, addr_t addr) {
  if (addr < DRAM_END_ADDRESS && addr >= DRAM_START_ADDRESS) {
    size_t index = addr - DRAM_START_ADDRESS;
    printf("0x%08x: 0x%04x%04x\n", addr, mem->data[index],
           mem->data[index + 1]);
  }
}

void print_mem_word(memory *mem, addr_t addr) {
  if (addr < DRAM_END_ADDRESS && addr >= DRAM_START_ADDRESS) {
    size_t index = addr - DRAM_START_ADDRESS;
    printf("0x%08x: 0x%02x%02x%02x%02x\n", addr, mem->data[index],
           mem->data[index + 1], mem->data[index + 2], mem->data[index + 3]);
  }
}

void mem_clear(memory *mem) {
  for (size_t i = 0; i < DRAM_SIZE; i++) {
    mem->data[i] = 0;
    mem->addr[i] = DRAM_START_ADDRESS + i;
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
    if (mem == NULL) {
      return 1;
    }
    mem_clear(mem);
  }

  // LOAD INSTRUCTIONS INTO MEMORY
  FILE *instr_file = fopen(OUTPUT_FILE_PATH, "r");
  if (!instr_file) {
    printf("instruction file open failed\n");
    return 1;
  }

  uint64_t num_instr = 0;
  instr_t instr;
  addr_t mem_addr;
  while (num_instr < MAX_INSTR_NUM &&
         fscanf(instr_file, "0x%x: 0x%x\n", &mem_addr, &instr) == 2) {
    // printf("0x%x: 0x%x\n", mem_addr, instr);
    mem_write(mem, mem_addr, (instr & 0x000000FF));
    mem_write(mem, mem_addr + 1, (instr & 0x0000FF00) >> 8);
    mem_write(mem, mem_addr + 2, (instr & 0x00FF0000) >> 16);
    mem_write(mem, mem_addr + 3, (instr & 0xFF000000) >> 24);
    num_instr++;
  }

  fclose(instr_file);

  return 0;
}
