#include "utils/elf_parser.h"

void extract_instructions(const char *elf_file_path) {
  FILE *elf_file = fopen(elf_file_path, "rb");
  if (!elf_file) {
    perror("Failed to open ELF file");
    return;
  }

  Elf32_Ehdr elf_header;
  fread(&elf_header, sizeof(Elf32_Ehdr), 1, elf_file);

  if (memcmp(elf_header.e_ident, ELFMAG, SELFMAG) != 0) {
    fprintf(stderr, "Not a valid ELF file.\n");
    fclose(elf_file);
    return;
  }

  fseek(elf_file, elf_header.e_shoff, SEEK_SET);
  Elf32_Shdr section_headers[elf_header.e_shnum];
  fread(section_headers, sizeof(Elf32_Shdr), elf_header.e_shnum, elf_file);

  FILE *output_file = fopen(OUTPUT_FILE_PATH, "w");
  if (!output_file) {
    perror("Failed to open output file");
    fclose(elf_file);
    return;
  }

  for (int i = 0; i < elf_header.e_shnum; i++) {
    if (section_headers[i].sh_type == SHT_PROGBITS &&
        section_headers[i].sh_flags & SHF_EXECINSTR) {
      fseek(elf_file, section_headers[i].sh_offset, SEEK_SET);
      uint8_t *instructions = malloc(section_headers[i].sh_size);
      if (!instructions) {
        perror("Memory allocation failed");
        fclose(output_file);
        fclose(elf_file);
        return;
      }
      fread(instructions, section_headers[i].sh_size, 1, elf_file);

      uint32_t base_address = section_headers[i].sh_addr;
      for (size_t j = 0; j < section_headers[i].sh_size; j += 4) {
        uint32_t instruction;
        memcpy(&instruction, &instructions[j], sizeof(uint32_t));
        instruction =
            __builtin_bswap32(instruction); // Convert from little-endian
        fprintf(output_file, "%08x: %08x\n", base_address + j, instruction);
      }
      free(instructions);
    }
  }

  fclose(output_file);
  fclose(elf_file);
}
