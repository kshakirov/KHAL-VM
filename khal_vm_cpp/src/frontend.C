#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<uint32_t> compile(string expression) {
  vector<uint32_t> result = {1, 2,2};
  cout << "Frontend: compiling expression {" << expression << " }" << endl;
  return result;
};
