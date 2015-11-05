#ifndef MY_DEFS
#define MY_DEFS

struct piece;
typedef piece* ppiece;

typedef enum color {
  black = 1,
  white
} color;

typedef enum gameStage {
  placement = 1,
  movement,
  mill
} gameStage;
#endif