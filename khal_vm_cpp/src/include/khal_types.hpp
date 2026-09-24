#pragma once
#include <vector>
enum class  Tag { INT, BOOL, NIL, FUNCTION, OBJECT };
enum class VmState {FLAT , IN_FUNCTION, EXECUTING_FUNCTION};
enum class OpCode {
  LOAD_INT,
  ADD_INT,
  PRINT_INT,
  FUNCTION_START,
  FUNCTION_END,
  CALL,
  RETURN
      };

struct Instruction{
  OpCode op;
  std::vector<int32_t> operands;
} ;
