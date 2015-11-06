#include "piece.h"

unsigned piece::count = 0;

piece::piece(color c) : id(count), mcolor(c){
  count++;
}

void piece::successor() {
}