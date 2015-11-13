#include <iostream>
#include "spot.h"
#include "scenario.h"
// spot
spot::spot(unsigned row, unsigned column, unsigned identifier) : r(row), c(column), id(identifier), n(0){
}

string spot::neighborsToStr() {
  string str = "";
  for(auto it = neighbors.begin(); it != neighbors.end(); ++it) {
    str += to_string((*it)->id);
    str += " ";
  }
  return str;
}

void spot::addNeighbor(int i) {
  neighbors.push_back(scenario[i]);
  n++;
}

void spot::printNeighbors(){
  cout << "node: " << id << endl;
  for(auto it = neighbors.begin(); it != neighbors.end(); ++it) {
    cout << " - " << (*it)->id << endl; 
  }
}