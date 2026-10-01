
#include <iostream>
#include <string>
#include <sys/types.h>
#include <vector>
#include "include/khal_types.hpp"
using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::string_view;


Instruction parse(string_view  line){
  Instruction instruction;
  instruction.op = OpCode::UNKNOWN;
  //  cout << "parse: " << line << endl;
  size_t space = 0;
  for(size_t i=0; i < line.size(); i++){
    if(line[i]== ' '){
      auto op = line.substr(0,i);
      if  (op == "LOAD_INT") {
	instruction.op = OpCode::LOAD_INT;
      }
      else if (op == "PRINT_INT"){
	instruction.op = OpCode::PRINT_INT;
      }
      else if (op=="ADD_INT") {
	instruction.op = OpCode::ADD_INT;
      }
      else if (op=="FUNCTION_START") {
	instruction.op = OpCode::FUNCTION_START;
      }
      else if (op=="FUNCTION_END") {
	instruction.op = OpCode::FUNCTION_END;
      }
      else if (op=="CALL") {
	instruction.op = OpCode::CALL;
      }
      else if (op=="RETURN") {
	instruction.op = OpCode::RETURN;
      }
      space =i ;
      
    }
    if(instruction.op != OpCode::UNKNOWN && i == line.length() - 1){
      cout << "ddd" <<endl;
      switch (instruction.op) {
      case OpCode::CALL:
      case OpCode::FUNCTION_END :
      case OpCode::FUNCTION_START:
      case OpCode::RETURN: {
	break;
      }
      default: {
	cout << " Parameter is " << line.substr(space + 1, i) <<endl;
	instruction.operands.push_back(1);
	instruction.operands.push_back(std::stoi(string(line.substr(space,i))));
      }
       
	
	  }
    }
    
    
  }
  
  return instruction;
}

  vector<Instruction> asm_parse(string code){
  vector<Instruction> v;
  size_t prev_n_line =0;
  for (size_t i = 0; i < code.size(); ++i) {
    if(code.at(i) == '\n'){
      cout << "start at " << prev_n_line << " end at " << i<< endl;
      auto instruction = parse(string_view(code).substr(prev_n_line, (i - prev_n_line)));
      v.push_back(instruction);
      prev_n_line = i + 1;
    }
  }
  return v;
}

int  main(void){
  string code = R"(LOAD_INT 222
LOAD_INT 333
ADD_INT
PRINT_INT
FUNCTION_START
LOAD_INT 200
LOAD_INT 300
ADD_INT
PRINT_INT
RETURN
FUNCTION_END
CALL
    )";

    asm_parse(code);
}
