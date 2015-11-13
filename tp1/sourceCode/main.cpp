#include <string>
#include <iostream>
#include "init.h"
#include "scenario.h"
#include "state.h"
#include "minMax.h"
#include "play.h"

void optLaunch() {
  readInputFile();
  createScenario(board);
  state* initial = new state();
  initial->init(board);
  pnode  root = new node(initial, nullptr);
  action* a;

  a = alphaBetaSearch(root, mcolor);
  a->print();
  
  for(auto it : lnodes) {
    delete it;
  }
  delete root;
}

void optPlay() {
  state* initial = new state();
  initial->init();
  char colorOpt;
  cout << "Chose your color: (b, w):" << endl;
  cin >> colorOpt;
  switch(colorOpt) {
    case 'b':
      mcolor = black;
      break;
    case 'w':
      mcolor = white;
      break;
    default:
      cout << "ERROR: in method play, bad color!";
      exit(1);
  }
  play(mcolor, initial);
}

int main(int argc, char** argv) {
  setUp();
  setUpScenario();
  switch(stoi(argv[1])) {
    case 1:
      optLaunch();
      break;
    case 2:
      optPlay();
      break;
    default:
      cout << "ERROR: main, bad args!" << endl;
      exit(1);
  }

  setDownScenario();
  setDown();
  return 0;
}