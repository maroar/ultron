#ifndef MY_INIT
#define MY_INIT
#include <string>
#include "defs.h"

using namespace std;

struct oldMove {
  bool none;
  string player, stage;
  int row, column;

  /*bool operator==(const oldMove& m) const {
   return (none == none) || 
     ( (player.compare(m.player)==0) );
  }*/
};
extern char**    board;
extern color     mcolor;
extern gameStage currentStage;
extern int       numBlack, numWhite;
extern int       numberOfPieces;
extern ppiece*   wp;
extern ppiece*   bp;

void allocPlayersPieces();
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