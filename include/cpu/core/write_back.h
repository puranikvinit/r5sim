#ifndef WRITE_BACK_H
#define WRITE_BACK_H

#include <stdio.h>

#include "cpu/core/mem_access.h"
#include "cpu/core/registers.h"

void write_back(write_back_data wb_data, register_file *reg_file);

#endif // !WRITE_BACK_H
