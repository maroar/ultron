#include <string>
#include <iostream>
#include "gameDefs.h"
#include "mill.h"
#include "movement.h"
#include "placement.h"

int main(int argc, char** argv) {
  setUp();
  readInputFile(); 
  //printInput();
  switch(currentStage) {
    case placement:
      action_placement();
      break;
    case movement:
      action_movement();
      break;
    case mill:
      action_mill();
      break;
    default:
      cout << "ERROR: currentStage" << endl;
      exit(1);
  }
  
  setDown();
  return 0;
}