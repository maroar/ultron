#ifndef MY_GAME_DEFS
#define MY_GAME_DEFS
#include <string>

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
};

char      board[7][7];
color     mColor;
gameStage currentStage;
int       numberOfPieces;
oldMove   move[3];
string    colorStr, stageStr;

void readInputFile();

#endif