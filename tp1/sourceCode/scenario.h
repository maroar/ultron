#ifndef MY_SCENARIO_DEF
#define MY_SCENARIO_DEF

#include "defs.h"
#include "spot.h"
#include "piece.h"
#include <vector>

extern spot***             mills;
extern vector<pointerSpot> scenario;

void createPiece(color pcolor, int r, int c, int id, int colorCount);
void createScenario(char** m);
void createMill(unsigned i, unsigned a, unsigned b, unsigned c);
void createMills();
void createSpotEdges();
void createSpot(int r, int c, int cnt);
void printMills();
void printScenario();
void setDownScenario();
void setUpScenario();
#endif