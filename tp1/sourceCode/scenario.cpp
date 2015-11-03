#include <iostream>
#include "scenario.h"
// scenario
scenario::scenario() {
  readScenario();
  spots.reserve(NUMBER_OF_SPOTS);
}

scenario::~scenario() {
  for(int i = 0; i < NUMBER_OF_SPOTS; i++) {
    delete spots[i];
  }
}

void scenario::readScenario() {
  unsigned numberOfEdges, neighborId;
  // create all spots
  for(int i = 0; i < NUMBER_OF_SPOTS; i++) {
    spots.push_back(new spot(i));
  }
  // read all edges
  for(int i = 0; i < NUMBER_OF_SPOTS; i++) {
    cin >> numberOfEdges;
    for(int j = 0; j < numberOfEdges; j++) {
      cin >> neighborId;
      spots[i]->neighbors.push_back(spots[neighborId]);
    }
  }
}