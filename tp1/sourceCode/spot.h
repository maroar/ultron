#ifndef MY_SPOT_DEF
#define MY_SPOT_DEF

#include <list>
#include <string>
#include "defs.h"

#define NUMBER_OF_SPOTS 24

struct  spot;
typedef spot* pointerSpot;

using namespace std;

struct spot {
  list<pointerSpot> neighbors;
  unsigned          id, r, c, n;

  spot(unsigned row, unsigned column, unsigned identifier);
  string neighborsToStr();
  string occupiedStr();
  void   addNeighbor(int i);
  void   printNeighbors();
};
#endif