#ifndef MY_SCENARIO_DEF
#define MY_SCENARIO_DEF

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

struct Scenario {
  char **scenario;
  int rows, columns;
  char* inputFile;
  
  void print();
  void readScenario();
  ~Scenario();
  Scenario(char* infile) : inputFile(infile) {
    readScenario();
  };
  
};

#endif