#ifndef MY_SPOT_DEF
#define MY_SPOT_DEF

#include <list>
#include <map>

#define NUMBER_OF_SPOTS 24

struct spot;

typedef spot* pointerSpot;

using namespace std;

extern unsigned spotcount;

struct spot {
  list<pointerSpot> neighbors;
  unsigned          id, r, c;
  bool              occupied;

  spot(unsigned row, unsigned column, unsigned identifier);
  bool isOccupied();
  bool isFree();
  void addNeighbor(pointerSpot n);
  void printNeighbors();
};
#endif