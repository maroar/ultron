#ifndef MY_SCENARIO_DEF
#define MY_SCENARIO_DEF

#include <iostream>

using namespace std;

struct Scenario {
  char **scenario;
  int rows, columns;
  
  Scenario() {};
  void readColumns();
  void readInput();
  void readScenario();
  void readRows();
};

#endif