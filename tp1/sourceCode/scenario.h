#ifndef MY_SCENARIO_DEF
#define MY_SCENARIO_DEF

#include "spot.h"
#include "piece.h"
#include <vector>

extern spot***   mills;
extern vector<pointerSpot> scenario;
extern unsigned            spotcount;

void createScenario(char**);
void setDownScenario();
void setUpScenario();
#endif