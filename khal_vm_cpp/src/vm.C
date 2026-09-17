#include "include/khal_types.hpp"
#include "vm.hpp"
#include <cassert>
using namespace std;

typedef struct {
  char tag;
  char bytes[8];
} RegisterOld;

// typedef enum { INT, BOOL, NIL } Tag;

typedef union {
  int32_t integer;
  bool boolean;

} Payload;

typedef struct {
  Tag tag;
  Payload payload;
} Register;

typedef int FuncTable[8];
FuncTable ft;
VmState vm_state;
void execute(vector<Instruction> bytecode) {
  Register registers[256];
  cout << "VM: executing bytecode [" << bytecode.size() << "] operants "
       << endl;
  auto start = std::begin(bytecode);
  auto finish = std::end(bytecode);

  for (auto it = start; it != finish; ++it) {
    switch (it->op) {
    case OpCode::LOAD_INT: {
      if (vm_state != VmState::IN_FUNCTION) {
        auto reg_num = it->operands.at(0);
        auto value = it->operands.at(1);
        assert(reg_num >= 0 && reg_num < 256);
        registers[reg_num].tag = Tag::INT;
        registers[reg_num].payload.integer = value;
      }
      break;
    }
    case OpCode::ADD_INT: {
      if (vm_state != VmState::IN_FUNCTION) {
        auto ra = it->operands.at(0);
        assert(ra >= 0 && ra < 256);
        assert(registers[ra].tag == Tag::INT); // for the time being
        auto rb = it->operands.at(1);
        assert(rb >= 0 && rb < 256);
        assert(registers[rb].tag == Tag::INT); // for the time being
        auto added =
            registers[ra].payload.integer + registers[rb].payload.integer;
        cout << "ADD:  " << registers[ra].payload.integer << " "
             << registers[rb].payload.integer << " added is  " << added << endl;
        registers[ra].payload.integer = added;
        cout << "Saved to Register " << endl;
      }
      break;
    }
    case OpCode::PRINT_INT: {
      if (vm_state != VmState::IN_FUNCTION) {
        auto ra = it->operands.at(0);
        assert(ra >= 0 && ra < 256);
        assert(registers[ra].tag == Tag::INT);
        cout << "PRINT_INT:  " << registers[ra].payload.integer << endl;
      }
      break;
    }
    case OpCode::FUNCTION_START: {
      if (vm_state == VmState::EXECUTING_FUNCTION) {
        // just go further
	cout << "FUNCTION START : EXEC  " << endl;
      } else {
        std::size_t i = std::distance(start, it);
        ft[0] = i; // хардкожу пока
	cout << "FUNCTION START : IN FUNC the jmp is   "<< i << endl;
      }
      break;
    }
    case OpCode::FUNCTION_END: {
      if (vm_state == VmState::EXECUTING_FUNCTION) {
        it = start + ft[0]; // хардкожу тоже не кричать
	vm_state = VmState::FLAT;
	cout << "FUNCTION END : EXEC  the jmp is   "<< ft[0]<< endl;
      } else {
	cout << "FUNCTION END: IN FUNC  " << endl;
        vm_state = VmState::FLAT;
      }
      break;
    }
    case OpCode::CALL: {
      if (vm_state == VmState::EXECUTING_FUNCTION) {
	vm_state=VmState::FLAT;
        // just go furhter
      } else {
        vm_state = VmState::EXECUTING_FUNCTION;
	std::size_t i = std::distance(start, it);
        it = start + ft[0]; // хардкожу тоже не кричать
	cout << "Back jump is " << i <<endl;
        ft[0] = i; // хардкожу пока
      }
      break;
    }
    }
  }
}
