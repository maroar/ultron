#ifndef MY_PIECE_DEF
#define MY_PIECE_DEF

#include "spot.h"
#include "defs.h"

struct piece {
  static unsigned   count;
  color             mcolor;
  unsigned          id;
  pointerSpot       pspot;
  list<pointerSpot> moves;

  piece(color c);
  void successor();
};

#endif