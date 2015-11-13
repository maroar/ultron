#include "play.h"

color     acolor, winner;
gameStage stage;
int       trow, tcol, drow, dcol;
state*    cstate;

bool  hasWinner() {
  return true;
}

color getActualColor(){
  return acolor;
}

gameStage getStage() {
  return stage;
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

  int cnt = 0;
  while(true) {
    if(acolor == mcolor) {
      playerPlays();
    }
    else {
      botPlays();
    }

    if(hasWinner()) break;
    //cnt++; if(cnt > 3) break;    
  }
}

void playerPlays() {
  cstate->print();
  readMove();
  
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
      break;
    case movement:
      cout << "movement:" << endl 
           << "target_row target_column destiny_row destiny_column" 
           << endl;
      cin >> trow;
      cin >> tcol;
      cin >> drow;
      cin >> dcol;
      break;
    case mill:
      cout << "mill:\n" 
           << "row column" 
           << endl;
      cin >> trow;
      cin >> tcol;
      break;
  }
}