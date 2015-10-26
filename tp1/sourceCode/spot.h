#ifndef MY_SPOT_DEF
#define MY_SPOT_DEF

#include <list>

#define NUMBER_OF_SPOTS 24

struct spot;

typedef spot* pspot;

using namespace std;

struct spot {
  list<pspot> neighbors;
  unsigned    id;
  bool        occupied;

  spot(unsigned);
  bool isOccupied();
  bool isFree();
  void printNeighbors();
};
#endif