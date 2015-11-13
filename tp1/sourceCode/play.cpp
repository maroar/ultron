#include "play.h"
#include <list>
#include <algorithm>

using namespace std;

bool      bfly, wfly;
color     acolor, winner;
gameStage stage;
int       trow, tcol, drow, dcol;
state*    cstate;

bool canIMoveToThere() {
  unsigned target = searchSpot(trow, tcol);
  if(cstate->spotIsFree(target)) {
    if(myColorCanfly()) {
      return true;
    }
    else {
      if(scenario[searchSpot(drow, dcol)]->hasNeighbor(target)) {
        return true;
      }
      else {
        cout << "ERROR: canIMoveToThere, are you kidding? The spot is so far! o0" << endl;
        return false;
      }
    }
  }
  else {
    cout << "ERROR: canIMoveToThere, busy spot!" << endl;
    return false;
  }
}

bool canIPutThere() {
  if(cstate->spotIsFree(searchSpot(trow, tcol))) {
    return true;
  }
  else {
    cout << "ERROR: you can not put a piece there!" << endl;
    return false;
  }
}

bool canIRemoveIt() {
  color          enemy       = invertColor(mcolor);
  list<unsigned> all;
  list<unsigned> outOfMills;
  int            spot        = searchSpot(trow, tcol);

  for(int i = 0; i < 24; i++) { // iterate over all spots in the board
    if(cstate->p[i] == enemy) { // select all of spots with the colors that I want
      if(!cstate->inMill(i, enemy)) {
        outOfMills.push_back(i);
      }
      all.push_back(i);
    }
  }

  if((find(outOfMills.begin(), outOfMills.end(), spot) != outOfMills.end())) {
    return true;
  }
  if(outOfMills.size() == 0) {
    return true;
  }
  else {
    cout << "ERROR: canIRemoveIt, you can not remove this piece! =x" << endl;
    return false;
  }
}

bool  hasWinner() {
  return true;
}

bool isAValidMove() {
  switch(stage) {
    case placement:
      return canIPutThere();
      break;
    case movement:
      return canIMoveToThere();
      break;
    case mill:
      return canIRemoveIt();
      break;
  }
}

bool myColorCanfly() {
  if(mcolor == white)
    return wfly;
  else
    return bfly;
}

bool verify(int r, int c) {
 cout << " " << r << " xxxxxxxxxxxxxxxxxxxx " << c << endl;
  for(int i = 0; i < 24; i++) {
 cout << " " << i << endl;   
    cout << "sr: " << scenario[i]->r << " sc: " 
         << scenario[i]->c << " (" << r << ", " << c << ")" << endl;
    if(scenario[i]->r == r && scenario[i]->c == c) {
      return true;
    }
  }

  return false;
}

color getActualColor(){
  return acolor;
}

gameStage getStage() {
  return stage;
}

int searchSpot(int i, int j) {
  if(i < 0)
    return 1000000;

  for(int i = 0; i < 24; i++) {
    if((scenario[i]->r == i) && (scenario[i]->c == j)) {
      return i;
    }
  }
}

void botPlays() {
  //
}

int numPlayerPieces() {
  switch(mcolor) {
    case black:
      return numBlack;
      break;
    case white:
      return numWhite;
      break;
    default:
      cout << "ERROR: numPlayerPieces, bad color!" << endl;
  }
}

void makeMove() {
  switch(stage) {
    case placement:
      //
      break;
    case movement:
      //
      break;
    case mill:
      //
      break;
  }
}

void play(color c, state* st) {
  acolor    = c;
  stage     = placement;
  cstate    = st;
  bfly      = false;
  wfly      = false;

  int cnt = 0;
  while(true) {
    //system("clear");
    if(acolor == mcolor) {
      playerPlays();
    }
    else {
      botPlays();
    }
    cstate->print();

    if(hasWinner()) break;
    acolor = invertColor(acolor);

    //cnt++; if(cnt > 3) break;    
  }
}

void playerPlays() {
  cstate->print();
  readMove();
  /*if(!isAValidMove()) {
    cout << "ERROR: playerPlays, bad move! =P" << endl;
    exit(1);
  }*/
  state* old = cstate;
  int    t, f;
  t = searchSpot(trow, tcol);
  f = searchSpot(trow, tcol);
  action* a = new action(returnKindOfAction(stage), mcolor, f, t);
  cstate    = old->makeState(a);

  delete a;
  delete old;
}

void readMove() {
  switch(stage) {
    case placement:
      cout << "placement (" 
           << (9-numPlayerPieces()) 
           << "):\nrow column" 
           << endl;
      cin >> trow;
      cin >> tcol;
      cout << " " << trow << " ************ " << tcol << endl;
      drow = -1;
      dcol = -1;
      if(!verify(trow, tcol)) {
        cout << "ERROR: readMove, wrong place." << endl;
        exit(1);
      }
      cout << " " << trow << " ************ " << tcol << endl;
      break;
    case movement:
      cout << "movement:" << endl 
           << "from_row from_column to_row to_column" 
           << endl;
      cin >> drow;
      cin >> dcol;
      cin >> trow;
      cin >> tcol;
      if(!verify(trow, tcol) || !verify(drow, dcol)) {
        cout << "ERROR: readMove, wrong place." << endl;
        exit(1);
      }
      break;
    case mill:
      cout << "mill:\n" 
           << "row column" 
           << endl;
      cin >> trow;
      cin >> tcol;
      drow = -1;
      dcol = -1;
      if(!verify(trow, tcol)) {
        cout << "ERROR: readMove, wrong place." << endl;
        exit(1);
      }
      break;
  }
}