#ifndef MY_PLAY
#define MY_PLAY

#define MAX_PIECES 9

#include <string>
#include <iostream>

#include "init.h"
#include "scenario.h"
#include "state.h"
#include "minMax.h"

bool      hasWinner();
bool      isAValidMove();
bool      myColorCanfly();
bool      verify(int r, int c);
color     getActualColor();
gameStage getStage();
int       numPlayerPieces();
int       searchSpot(int r, int c);
void      botPlays(color c);
void      makeMove();
void      play(color c, state* st);
void      playerPlays();
void      readMove();

#endif