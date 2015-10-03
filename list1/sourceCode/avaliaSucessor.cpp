#include "PacMaze.h"
#include <string>  

using namespace std;

string::size_type sz;

int main(int argc, char** argv) {
  pacMaze = new PacMaze(argv[1], stoi(argv[2], &sz), stoi(argv[3], &sz));
  pacMaze->successor(pacMaze->pacMan->getRow(), pacMaze->pacMan->getColumn());
  pacMaze->printSuccessor();
  
  delete pacMaze;
  return 0;
}

