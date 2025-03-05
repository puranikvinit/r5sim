#ifndef FETCH_H
#define FETCH_H

#include "config_defines.h"
#include "cpu/core/registers.h"
#include "cpu/core/instr_decode.h"
#include "memory/memory.h"

extern register_file *reg_file;

instr_t fetch_instruction(memory *mem, reg_t *pc);

#endif // !FETCH_H
