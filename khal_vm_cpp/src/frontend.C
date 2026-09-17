
#include "frontend.hpp"
#include "include/khal_types.hpp"
#include <string>
#include <vector>
using namespace std;


vector<Instruction> _compile_a(string expression) {
  Instruction instruction_a, instruction_b, instruction_c, instruction_d, instruction_f;
  instruction_a.op = OpCode::LOAD_INT;
  instruction_a.operands = {1,222}; //1 register
  instruction_b.op = OpCode::LOAD_INT;
  instruction_b.operands ={2,333};
  instruction_c.op = OpCode::ADD_INT;
  instruction_c.operands = {1,2}; //registers
  instruction_d.op = OpCode::PRINT_INT;
  instruction_d.operands = {1};
  vector<Instruction> instructions;
  instructions.push_back(instruction_a);
  instructions.push_back(instruction_b);
  instructions.push_back(instruction_c);
  instructions.push_back(instruction_d);
  
  
  cout << "Frontend: compiling expression {" << expression << " }" << endl;
  return instructions;
};

vector<Instruction> _compile_b(string expression) {
  Instruction instruction_a, instruction_b, instruction_c, instruction_d, instruction_f, instruction_e;
  
  instruction_a.op = OpCode::FUNCTION_START;
  instruction_b.op = OpCode::LOAD_INT;
  instruction_b.operands = {1,222}; //1 register
  instruction_f.op = OpCode::RETURN;
  instruction_c.op =OpCode::FUNCTION_END;
  instruction_e.op = OpCode::CALL;
  instruction_d.op = OpCode::PRINT_INT;
  instruction_d.operands = {1};
  vector<Instruction> instructions;
  instructions.push_back(instruction_a);
  instructions.push_back(instruction_b);
  instructions.push_back(instruction_f);
  instructions.push_back(instruction_c);
  instructions.push_back(instruction_e);
  instructions.push_back(instruction_d);
  
  
  
  
  cout << "Frontend: compiling expression {" << expression << " }" << endl;
  return instructions;
};

vector<Instruction> compile(string expression){
  return _compile_b(expression);
}
