
#include "frontend.hpp"
using namespace std;


vector<Instruction> compile(string expression) {
  Instruction instruction_a, instruction_b, instruction_c;
  instruction_a.op = OpCode::LOAD_INT;
  instruction_a.operands = {1,222}; //1 register
  instruction_b.op = OpCode::LOAD_INT;
  instruction_b.operands ={2,333};
  instruction_c.op = OpCode::ADD_INT;
  instruction_c.operands = {1,2}; //registers
  
  vector<Instruction> instructions;
  instructions.push_back(instruction_a);
  instructions.push_back(instruction_b);
  instructions.push_back(instruction_c);
  
  cout << "Frontend: compiling expression {" << expression << " }" << endl;
  return instructions;
};
