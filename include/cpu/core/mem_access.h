#ifndef MEM_ACCESS_H
#define MEM_ACCESS_H

#include "registers.h"

typedef struct {
  uint8_t rd;
  reg_t write_data;
} write_back_data;

#endif // !MEM_ACCESS_H
