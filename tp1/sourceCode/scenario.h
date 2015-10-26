#ifndef MY_SCENARIO_DEF
#define MY_SCENARIO_DEF

#include "spot.h"
#include "piece.h"
#include <vector>

struct scenario {
  vector<pspot> spots;

  scenario();
  ~scenario();
  void readScenario();
};
#endif