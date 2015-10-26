#ifndef MY_PIECE_DEF
#define MY_PIECE_DEF

#include "spot.h"

struct piece {
  unsigned    id;
  pspot       _spot;
  list<pspot> moves;

  piece();
  void successor();
};

#endif