#include "Scenario.h"
using namespace std;

int main(int argc, char** argv) {
  int i;
  cout << "Args: " << endl;
  for(i = 0; i < argc; i++) {
    cout << "  " << argv[i] << endl;
  }
  return 0;
}

