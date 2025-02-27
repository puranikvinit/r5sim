#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <elf.h>

/**
 * @brief Extracts instructions from an ELF file and writes them to a text file
 *
 * This function scans an ELF file for executable sections, extracts all
 * instructions, and writes them to an output file in the format:
 * "address: instruction" where both values are in hexadecimal.
 *
 * @param elf_file_path Path to the input ELF file
 * @param output_file_path Path to the output text file
 */
void extract_instructions(const char* elf_file_path, const char* output_file_path);

#endif //!PARSER_H