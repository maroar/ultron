#ifndef MY_INIT
#define MY_INIT
#include <string>
#include <list>
#include <stdlib.h>

#include "defs.h"

using namespace std;

struct oldMove {
  bool      none;
  color     player;
  gameStage stage;
  int       row, column, orow, ocolumn;
};
struct action;
struct state;

extern bool          flyWhite, flyBlack;
extern char**        board;
extern color         mcolor;
extern gameStage     currentStage;
extern int           numBlack, numWhite;
extern int           numberOfPieces;
extern oldMove       oldmove[3];
extern ppiece*       wp;
extern ppiece*       bp;

bool     addMove(bool n, color p, gameStage s, int r, int c);
color    invertColor(color c);
unsigned mrand();
void     allocPlayersPieces();
void     printBoard();
void     printColor(color c);
void     printInput();
void     printMColor();
void     printMove(unsigned index);
void     readBoard();
void     readInputFile();
void     readMove(unsigned index);
void     setDown();
void     setUp();
void     setUpVariables();

#endif