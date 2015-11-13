#include "state.h"
#include "scenario.h"

#include <iostream>

#define POINT_PLACES 10  
#define MILL_VALUE   1000

using namespace std;

bool state::inMill(unsigned i, color c) {
  for(int i = 0; i < 16; i++) {
    if(p[mills[i][0]->id] == c &&
       p[mills[i][1]->id] == c &&
       p[mills[i][2]->id] == c) {
      if((mills[i][0]->id) || (mills[i][1]->id == i) || (mills[i][2]->id == i) )
        return true;
      else
        return false;
    }
  }
}

bool state::matchMill(unsigned i, color c) {
  if(p[mills[i][0]->id] == c &&
     p[mills[i][1]->id] == c &&
     p[mills[i][2]->id] == c)
    return 1;
  else
    return 0;
}

bool state::spotIsFree(unsigned i) {
  return p[i] == nocolor;
}

int state::getScoreMill(color c) {
  return 1;
}

int state::getScoreMove(color c) {
  if(score > -1) {
    return score;
  }
  color e = invertColor(c);
  score   =  mrand();
  score  += pointsForPlaces(c);
  score  += pointsForMills(c);
  score  -= pointsForPlaces(e);
  score  -= pointsForMills(e);

  return score;
}

int state::getScorePlacement(color c) {
  if(score > -1) {
    return score;
  }
  color e = invertColor(c);
  score   =  mrand();
  score  += pointsForPlaces(c);
  score  += pointsForMills(c);
  score  -= pointsForPlaces(e);
  score  -= pointsForMills(e);

  return score;
}

int state::numberOfBlackMills(){
  if(cntBlackMills > -1) {
    return cntBlackMills;
  }
  cntBlackMills = numberOfMills(black);
  return cntBlackMills;
}

int state::numberOfMills(color c){
  int cntMills = 0;
  for(int i = 0; i < 16; i++) {
    cntMills += matchMill(i, c);
  }
  return cntMills;
}

int state::numberOfWhiteMills(){
  if(cntWhiteMills > -1) {
    return cntWhiteMills;
  }
  cntWhiteMills = numberOfMills(white);
  return cntWhiteMills;
}
// points gained for buil a mill
int state::pointsForMills(color c) {
  switch(c) {
    case white:
      if(numberOfWhiteMills() > parent->numberOfWhiteMills())
        return MILL_VALUE;
      else
        return 0; 
      break;
    case black:
      if(numberOfBlackMills() > parent->numberOfBlackMills())
        return MILL_VALUE;
      else
        return 0; 
      break;
    default:
      cout << "ERROR: pointsForMills, wrong color" << endl;
      exit(1);
  }
}
// points for actual mobility
int state::pointsForMobility(unsigned i) {
  int moves = 0;
  for(auto it : scenario[i]->neighbors) {
    if(spotIsFree(it->id)) {
      moves += 10;
    }
  }
  return moves;
}
// points are calculaed as the number of spaces to move
int state::pointsForPlaces(color c) {
  int ret = 0;
  for(int i = 0; i < 24; i++) {
    if(p[i] == c) {
      ret += POINT_PLACES * scenario[i]->n;
      ret += pointsForMobility(i);
    }
  }
  return ret;
}

state* state::makeState(action* a) {
  state* st = new state();
  st->parent = this;
  for(int i = 0; i < 24; i++) {
    st->p[i] = p[i];
  }
  switch(a->kind) {
    case put_piece:
      st->put(a);
      break;
    case move_piece:
      st->move(a);
      break;
    case remove_piece:
      st->remove(a);
      break;
  }
  return st;
}

void printSpot(color c) {
  switch(c) {
    case black:
      cout << "B";
      break;
    case white:
      cout << "W";
      break;
    case nocolor:
      cout << "o";
      break;
    default:
      cout << "ERROR: printColor" << endl;
      exit(1);
  }
}

void state::move(action* a) {
  unsigned oldplace = scenario[a->o]->id;
  unsigned newplace = scenario[a->t]->id;
  p[newplace] = p[oldplace];
  p[oldplace] = nocolor;
}

void state::put(action* a) {
  unsigned newplace = scenario[a->t]->id;
  p[newplace] = a->acolor;
}

void state::remove(action* a) {
  unsigned newplace = scenario[a->t]->id;
  p[newplace] = nocolor;
}

void state::init() {
  for(int i = 0; i < 24; i++) {
    p[i] = nocolor;
  }
}

void state::init(char** m) {
  for(int i = 0; i < 24; i++) {
    switch(m[scenario[i]->r][scenario[i]->c]) {
      case 'B':
        p[i] = black;
        break;
      case 'W':
        p[i] = white;
        break;
      default:
        p[i] = nocolor;
        break;
    }
  }
}

void state::print() {
  cout << "  0123456" << endl;
  cout << "0 ";print(0); cout << "--"; print(1); cout << "--"; print(2); cout << endl;
  cout << "1 ";cout << "|"; print(3); cout << "-"; print(4); cout << "-"; print(5); cout << "|"; cout << endl; 
  cout << "2 ";cout << "|"; cout << "|"; print(6); print(7); print(8); cout << "|"; cout << "|"; cout << endl;
  cout << "3 ";print(9); print(10); print(11); cout << "+"; print(12); print(13); print(14); cout << endl;
  cout << "4 ";cout << "|"; cout << "|"; print(15); print(16); print(17); cout << "|"; cout << "|"; cout << endl;
  cout << "5 ";cout << "|"; print(18); cout << "-"; print(19); cout << "-"; print(20); cout << "|"; cout << endl;
  cout << "6 ";print(21); cout << "--"; print(22); cout << "--"; print(23); cout << endl;
  cout << "_____________________________" << endl;
}

void state::print(unsigned i){
  printSpot(p[i]);
}