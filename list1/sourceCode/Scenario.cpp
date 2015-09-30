#include "Scenario.h"

void Scenario::print() {
  for(int i = 0; i < rows; i++) {
      for(int j = 0; j < columns; j++) {
        cout << scenario[i][j];
      }
      cout << endl;
  }
}

void Scenario::readScenario() {
  int i, j;
  fstream myfile(inputFile, fstream::in);
  if (myfile.is_open()) {
    myfile >> rows;
    myfile >> columns;
    scenario = new char *[rows];
    for(i = 0; i < rows; i++)
      scenario[i] = new char [columns]; 
    for(i = 0; i < rows; i++) {
      for(j = 0; j < columns; j++) {
        myfile >> skipws >> scenario[i][j];
      }
    }
    myfile.close();
  }
  else
    cout << "Unable to open file \"" << inputFile << "\"" << endl; 
}

Scenario::~Scenario() {
  for (int i = 0; i < rows; i++)
    delete[] scenario[i];
  delete[] scenario;
}