#include "include/khal_types.hpp"
#include "vm.hpp"
#include <cassert>
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
      registers[reg_num].tag = Tag::INT;
      registers[reg_num].payload.integer= value;
      break;
    }
    case OpCode::ADD_INT:{

      auto ra = it->operands.at(0);
      assert(registers[ra].tag == Tag::INT); // for the time being
      auto rb = it->operands.at(1);
      assert(registers[rb].tag == Tag::INT); // for the time being
      auto added = registers[ra].payload.integer +  registers[rb].payload.integer ;
      cout << "ADD:  " <<  registers[ra].payload.integer << " " << registers[rb].payload.integer << " added is  " << added <<endl;
      break;  
    }
    case OpCode::PRINT_INT:{
      auto ra = it->operands.at(0);
      cout << "PRINT_INT:  " <<  registers[ra].payload.integer  << endl;
      break;
      
    }

      
    }

  }
}
