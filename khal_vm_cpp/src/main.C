#include <cstdint>
using namespace  std;
#include <iostream>
#include "frontend.hpp"
#include <vector>
int main(int argc, char** argv){
  
  if (argc < 2) {
    cout << "KHAL-VM: You must provide an expression as an agrument to make me work for you"<<endl;
  }else {
    cout << "KHAL-VM: You provided an expression " << argv[1]
         << "  working on it ..." << endl;
    
    auto r = compile(argv[1]);
  }
}
