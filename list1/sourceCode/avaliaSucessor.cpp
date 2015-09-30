#include "Scenario.h"
using namespace std;

int main(int argc, char** argv) {
  Scenario * scenario = new Scenario(argv[1]);
  scenario->print();
  
  delete scenario;
  return 0;
}

