#ifndef MY_MINMAX
#define MY_MINMAX

#include "searchGraph.h"

#define MAX_DEPTH 4 // max = 18 (placement)
#define PINF  1000000000
#define NINF -1000000000

int     maxValue(pnode n, int a, int b, unsigned p, color c);
int     minValue(pnode n, int a, int b, unsigned p, color c);
action* alphaBetaSearch(pnode r, color c);

#endif
