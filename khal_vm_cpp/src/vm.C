#include "vm.hpp"
using namespace std;

typedef struct {
  char tag;
  char bytes[8];
} RegisterOld;

//typedef enum { INT, BOOL, NIL } Tag;

typedef union {
  int32_t integer;
  bool boolean;

} Payload;

typedef struct {
  Tag tag;
  Payload payload;
} Register;

void execute(vector<Instruction> bytecode) {
  Register registers[256];
  cout << "VM: executing bytecode [" << bytecode.size() << "] operants "
       << endl;
  auto start = std::begin(bytecode);
  auto finish = std::end(bytecode);

  for (auto it = start; it != finish; ++it) {
    switch (it->op) {
    case OpCode::LOAD_INT: {
      auto reg_num = it->operands.at(0);
      auto value = it->operands.at(1);
      registers[reg_num].tag = INT;
      registers[reg_num].payload.integer= value;
      break;
    }
    case OpCode::ADD_INT:{
      auto ra = it->operands.at(0);
      auto rb = it->operands.at(1);
      cout << "ADD:  " <<  registers[ra].payload.integer << " " << registers[rb].payload.integer << endl;
      break;  
    }
    case OpCode::PRINT_INT:{
      auto ra = it->operands.at(0);
      cout << "PRINT_INT:  " <<  registers[ra].payload.integer  << endl;
      
    }

      
    }

  }
}
