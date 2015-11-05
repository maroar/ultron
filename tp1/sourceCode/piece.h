#ifndef MY_PIECE_DEF
#define MY_PIECE_DEF

#include "spot.h"

struct piece {
  unsigned          id;
  pointerSpot       pspot;
  list<pointerSpot> moves;

  piece();
  void successor();
};

#endif