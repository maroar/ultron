#include <iostream>
#include "spot.h"
#include "scenario.h"
// spot
spot::spot(unsigned row, unsigned column, unsigned identifier) : r(row), c(column), id(identifier), occupied(false){
}

bool spot::isFree(){
  return !occupied;  
}

bool spot::isOccupied(){
  return occupied;
}

string spot::neighborsToStr() {
  string str = "";
  for(auto it = neighbors.begin(); it != neighbors.end(); ++it) {
    str += to_string((*it)->id);
    str += " ";
  }
  return str;
}

string spot::occupiedStr() {
  return occupied ? "(occupied)" : "(not occupied)";
}

void spot::addNeighbor(int i) {
  neighbors.push_back(scenario[i]);
}

void spot::printNeighbors(){
  cout << "node: " << id << endl;
  for(auto it = neighbors.begin(); it != neighbors.end(); ++it) {
    cout << " - " << (*it)->id << endl; 
  }
}