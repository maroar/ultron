#ifndef MY_GAME_DEFS
#define MY_GAME_DEFS
#include <string>
#include "scenario.h"

using namespace std;

typedef enum color {
  black = 1,
  white
} color;

typedef enum gameStage {
  placement = 1,
  movement,
  mill
} gameStage;

struct oldMove {
  bool none;
  string player, stage;
  int row, column;

  /*bool operator==(const oldMove& m) const {
   return (none == none) || 
     ( (player.compare(m.player)==0) );
  }*/
};

extern color     mcolor;
extern gameStage currentStage;
extern int       numBlack, numWhite;
extern int       numberOfPieces;

void printBoard();
void printInput();
void printMove(unsigned index);
void readBoard();
void readInputFile();
void readMove(unsigned index);
void setDown();
void setUp();
void setUpVariables();

#endif