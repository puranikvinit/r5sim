#include "cpu/core/registers.h"
#include "memory/memory.h"
#include "utils/config_parser.h"
#include "utils/elf_parser.h"

register_file *reg_file;
memory *mem;

int main(int argc, char *argv[]) {
  if (!parse_configs())
    return 1;

  if (!extract_instructions(argv[1]))
    return 1;

  reg_file_init(reg_file);

  if (!mem_init())
    return 1;

  return 0;
}
