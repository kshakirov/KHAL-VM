#include <iostream>
#include <vector>
using namespace std;

typedef struct {
  char tag;
  char bytes[8];
}Register;
void execute(vector<uint32_t> bytecode) {
  Register registers[256];
  cout << "VM: executing bytecode [" << bytecode.size() << "] operants "
       << endl;
    auto start = std::begin(bytecode) + 1;
    auto finish = std::end(bytecode);
    int i = 1;
    for (auto it = start; it != finish; ++it) {
      std::cout << *it << " "; // Output: 30 40 50
      registers[i].tag = 1;
      registers[i].bytes[0]= *it;
      
    }
}
