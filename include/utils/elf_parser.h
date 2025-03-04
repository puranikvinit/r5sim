#ifndef PARSER_H
#define PARSER_H

#ifndef OUTPUT_FILE_PATH
#define OUTPUT_FILE_PATH "instructions.txt"
#endif

#include <elf.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Extracts instructions from an ELF file and writes them to a text file
 *
 * This function scans an ELF file for executable sections, extracts all
 * instructions, and writes them to an output file in the format:
 * "address: instruction" where both values are in hexadecimal.
 *
 * @param elf_file_path Path to the input ELF file
 * @param output_file_path Path to the output text file
 *
 * @return 0 on success, non-zero on failure
 * 1: file open/read failure
 * 2: invalid ELF file
 * 3: memory allocation failure
 */
int extract_instructions(const char *elf_file_path);

#endif //! PARSER_H
