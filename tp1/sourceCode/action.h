#ifndef MY_ACTION
#define MY_ACTION

#include "init.h"

#include <string>

typedef enum kindOfAction {
  put_piece = 0,
  move_piece,
  remove_piece,
  none
} kindOfAction;

struct action {
  kindOfAction kind;
  color        acolor; // action color
  unsigned     o, t;// origin | target
  action(kindOfAction k, color c, unsigned orig, unsigned target) 
    : kind(k), acolor(c), o(orig), t(target) {};
  string toString();
  void   print();
};

kindOfAction returnKindOfAction(gameStage g);

#endif
