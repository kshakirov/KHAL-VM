#pragma once
#include <vector>
typedef enum { INT, BOOL, NIL } Tag;

enum class OpCode { LOAD_INT, ADD_INT, PRINT_INT };

typedef struct{
  OpCode op;
  std::vector<int32_t> operands;
} Instruction;
