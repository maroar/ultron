#include <iostream>
#include "spot.h"
// spot
spot::spot(unsigned row, unsigned column, unsigned identifier) : r(row), c(column), id(identifier), occupied(false){
}

bool spot::isFree(){
  return !occupied;  
}

bool spot::isOccupied(){
  return occupied;
}

void spot::addNeighbor(pointerSpot n) {
  neighbors.push_back(n);
}

void spot::printNeighbors(){
  cout << "node: " << id << endl;
  for(auto it = neighbors.begin(); it != neighbors.end(); ++it) {
    cout << " - " << (*it)->id << endl; 
  }
}