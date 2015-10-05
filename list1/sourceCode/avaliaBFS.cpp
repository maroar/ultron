#include "PacMaze.h"
#include <string>  

using namespace std;

string::size_type sz;

int main(int argc, char** argv) {
  pacMaze = new PacMaze(argv[1], stoi(argv[2], &sz), stoi(argv[3], &sz));
  sg      = new SearchGraph(pacMaze->pacMan->getRow(), pacMaze->pacMan->getColumn(), 0);
  sg->bfs();

  delete sg;
  delete pacMaze;
  return 0;
}