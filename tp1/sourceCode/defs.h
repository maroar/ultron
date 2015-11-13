#ifndef MY_DEFS
#define MY_DEFS

struct piece;
typedef piece* ppiece;

typedef enum color {
  black = 0,
  white,
  nocolor
} color;

typedef enum gameStage {
  placement = 0,
  movement,
  mill
} gameStage;
#endif