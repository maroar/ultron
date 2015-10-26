#include <iostream>
#include "spot.h"
// spot
spot::spot(unsigned _id) : id(_id), occupied(false){
}

bool spot::isFree(){
  return !occupied;  
}

bool spot::isOccupied(){
  return occupied;
}

void spot::printNeighbors(){
  cout << "node: " << id << endl;
  for(auto it = neighbors.begin(); it != neighbors.end(); ++it) {
    cout << " - " << (*it)->id << endl; 
  }
}