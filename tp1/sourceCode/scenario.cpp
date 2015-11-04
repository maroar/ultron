#include "scenario.h"
// scenario
spot***              mills;
unsigned            spotcount;
vector<pointerSpot> scenario;

void createScenario(char** m) {
  for(int i = 0; i < 7; i++) {
    for(int j = 0; j < 7; j++) {
      switch(m[i][j]) {
        case 'B':
        case 'W':
        case 'o':
          //create new spot
          break;
        default:
          break;
      }
    }
  }
}

void setDownScenario() {
  for(int i = 0; i < 16; i++) {
    free(mills[i]);
  }
  free(mills);
}

void setUpScenario() {
  scenario.reserve(24);
  spotcount = 0;
  mills = (pointerSpot**) malloc(16 * sizeof(pointerSpot*));
  for(int i = 0; i < 16; i++) {
    mills[i] =  (pointerSpot*) malloc(3 * sizeof(spot***));
  }
}