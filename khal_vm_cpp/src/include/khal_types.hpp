#pragma once
#include <vector>
 enum class  Tag { INT, BOOL, NIL };

enum class OpCode { LOAD_INT, ADD_INT, PRINT_INT };

struct Instruction{
  OpCode op;
  std::vector<int32_t> operands;
} ;
