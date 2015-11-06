#ifndef MY_SPOT_DEF
#define MY_SPOT_DEF

#include <list>
#include <string>
#include "defs.h"

#define NUMBER_OF_SPOTS 24

struct  spot;
typedef spot* pointerSpot;
struct  piece;
typedef piece* pointerPiece;

using namespace std;

struct spot {
  bool              occupied;
  list<pointerSpot> neighbors;
  pointerPiece      ppiece;
  unsigned          id, r, c;

  spot(unsigned row, unsigned column, unsigned identifier);
  bool   isOccupied();
  bool   isFree();
  color  mcolor();
  string neighborsToStr();
  string occupiedStr();
  void   addNeighbor(int i);
  void   printNeighbors();
};
#endif