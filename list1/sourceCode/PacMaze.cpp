#include "PacMaze.h"
#include <cmath>
int                 expandCount;
int                 numNodes;
list<pair<int,int>> explored;
list<Move*>         moves;
list<Node*>         fringe;
PacMaze             *pacMaze;
SearchGraph         *sg;
// helper methods
bool alreadyVisited(int row, int column) {
  pair<int,int> targer;
  targer.first  = row;
  targer.second = column;
  return (find(explored.begin(), explored.end(), targer) != explored.end());
}

string directionToString(direction d) {
  switch(d) {
    case NORTH: return "acima";
    case SOUTH: return "abaixo";
    case EAST:  return "direita";
    case WEST:  return "esquerda";
    default:    return "null";
  }
}

void printFringe() {
  list<Node*>::const_iterator it;
  for(it = fringe.begin(); it != fringe.end(); ++it) {
    cout << (*it)->toString() << " "; 
  }
  cout << endl;
}

string shape(bool v) {
  if(v)
    return "box";
  else
    return "circle";
}
// Goal methods
bool Goal::isGoal(int row, int column) {
  return (row == r) && (column == c);
}

void Goal::print() {
  cout << "row: " << r << " col: " << c << endl;
}
// Move methods
string Move::toString() {
  string toReturn = "(";
  toReturn += directionToString(d);
  toReturn += ";";
  toReturn += to_string(r);
  toReturn += ",";
  toReturn += to_string(c);
  toReturn += ")";
  return   toReturn;
}
// PacMaze methods
bool PacMaze::canMoveTo(int x, int y, direction d){
  switch(d) {
    case NORTH: return (scenario[(x-1)%rows][y]) != '#';
    case SOUTH: return (scenario[(x+1)%rows][y]) != '#';
    case EAST:  return (scenario[x][(y+1)%columns]) != '#';
    case WEST:  return (scenario[x][(y-1)%columns]) != '#';
    default:    return false;
  }
}

void PacMaze::findGoal() {
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      if(scenario[i][j]==GOAL) {
        goal = new Goal(i, j);
        return;
      }
    }
  }
}

int PacMaze::movePacManTo(direction d) {
  if(canMoveTo(pacMan->getRow(), pacMan->getColumn(), d)) {
    switch(d) {
      case NORTH: pacMan->moveTo((pacMan->getRow()-1)%rows, pacMan->getColumn()); break;
      case SOUTH: pacMan->moveTo((pacMan->getRow()+1)%rows, pacMan->getColumn()); break;
      case EAST:  pacMan->moveTo(pacMan->getRow(), (pacMan->getColumn()+1)%columns); break;
      case WEST:  pacMan->moveTo(pacMan->getRow(), (pacMan->getColumn()-1)%columns); break;
      default:    break;
    }
    return successor(pacMan->getRow(), pacMan->getColumn());
  }
  return 0;
}

void PacMaze::print() {
  putPacManInScenario();
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      cout << scenario[i][j];
    }
    cout << endl;
  }
  removePacManFromScenario();
}

void PacMaze::putPacManInScenario() {
  charBeforePacMan = scenario[pacMan->getRow()][pacMan->getColumn()];
  scenario[pacMan->getRow()][pacMan->getColumn()] = 'P';
}

void PacMaze::printScenario() {
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      cout << scenario[i][j];
    }
    cout << endl;
  }
}

void PacMaze::printSuccessor() {
  list<Move*>::const_iterator iterator;
  for(iterator = moves.begin(); iterator != moves.end(); ++iterator) {
    cout << (*iterator)->toString() << " ";
  }
  cout << endl;
}

void PacMaze::readScenario() {
  int i, j;
  fstream myfile(inputFile, fstream::in);
  if(myfile.is_open()) {
    myfile >> rows;
    myfile >> columns;
    scenario = new char *[rows];
    for(i = 0; i < rows; i++)
      scenario[i] = new char [columns]; 
    for(i = 0; i < rows; i++) {
      for(j = 0; j < columns; j++) {
        myfile >> skipws >> scenario[i][j];
      }
    }
    myfile.close();
  }
  else
    cout << "Unable to open file \"" << inputFile << "\"" << endl; 
}

void PacMaze::removePacManFromScenario() {
  scenario[pacMan->getRow()][pacMan->getColumn()] = charBeforePacMan;
}

int PacMaze::successor(int x, int y) {
  int i = 0;
  moves.clear();
  if(canMoveTo(x, y, NORTH)){
    moves.push_back(new Move(NORTH, (x-1)%rows, y));
    i++;
  }
  if(canMoveTo(x, y, SOUTH)){
    moves.push_back(new Move(SOUTH, (x+1)%rows, y));
    i++;
  }
  if(canMoveTo(x, y, WEST)){
    moves.push_back(new Move(WEST, x, (y-1)%columns));
    i++;
  }
  if(canMoveTo(x, y, EAST)){
    moves.push_back(new Move(EAST, x, (y+1)%columns));
    i++;
  }
  return i;
}

PacMaze::~PacMaze() {
  for(int i = 0; i < rows; i++)
    delete[] scenario[i];
  delete[] scenario;
  delete pacMan;
  delete goal;
}
// exerc 2
// Node
Node::~Node() {
  if(children.size()!=0) {
    list<Node*>::const_iterator iterator;
    for(iterator = children.begin(); iterator != children.end(); ++iterator) {
      delete *iterator;
    }
  }
}

float Node::distanceToGoal() {
  float x = r - pacMaze->goal->r;
  float y = c - pacMaze->goal->c;
  return sqrt(x*x + y*y);
}

void Node::expand() {
  list<Move*>::const_iterator it;
  expandAt = expandCount++;
  pacMaze->successor(r, c);
  for(it = moves.begin(); it != moves.end(); ++it) {
    children.push_back(new Node(this, cost+1.0, (*it)->r, (*it)->c, (*it)->d));
  }
  explored.push_back(make_pair(r,c));
}

void Node::printDot() {
  cout << " n" << id << " [shape=" << shape(visited) << " label=\"" << toDot() << "\"]" << endl;
  if(parent)
    cout << " n" << id << " -- n" << parent->id << endl; 
  list<Node*>::const_iterator iterator;
  for(iterator = children.begin(); iterator != children.end(); ++iterator) {
    (*iterator)->printDot();
  }
}

void Node::printChildren() {
  list<Node*>::const_iterator iterator;
  for(iterator = children.begin(); iterator != children.end(); ++iterator) {
    cout << (*iterator)->toString() << " "; 
  }
  cout << endl;
}

void Node::removeNodeFromFringe() {
  list<Node*>::const_iterator it;
  for(it = fringe.begin(); it != fringe.end(); ++it) {
    if((*it)->id == id) {
      fringe.remove(*it);
      break;
    } 
  }
}

string Node::toDot() {
  string str =  "id: (" + to_string(id) + ")\\n";
  str += "expand: (" + to_string(expandAt) + ")\\n";
  str += "state: (" + to_string(r) + "," + to_string(c) + ")\\n";
  str += "action: " + directionToString(d) + "\\n";
  str += "cost: " + to_string(cost) + "\\n";
  str += "hcost: " + to_string(hcost) + "\\n";
  return str;
}

string Node::toString() {
  string toReturn = "(";
  toReturn += directionToString(d);
  toReturn += ";";
  toReturn += to_string(r);
  toReturn += ",";
  toReturn += to_string(c);
  toReturn += ";";
  toReturn += to_string(int(cost));
  toReturn += ";";
  if(parent) {
    toReturn += to_string(parent->r);
    toReturn += ",";
    toReturn += to_string(parent->c);
  }
  else
    toReturn += "-1,-1";
  toReturn += ")";
  return toReturn;
}
// SearchGraph
SearchGraph::~SearchGraph() {
  delete root;
}

bool SearchGraph::nodeIsGoal(Node *n) {
  return pacMaze->goal->isGoal(n->r, n->c);
}

void SearchGraph::printDot() {
  cout << "graph name {" << endl;
  root->printDot();
  cout << "\n}" << endl;
}

void SearchGraph::solution(Node *n) {
  list<direction> sol;
  direction d;

  do {
    sol.push_back(n->d);
    n = n->parent;
  }
  while(n != NULL);

  sol.pop_back();
  while(!sol.empty()) {
    d = sol.back();
    sol.pop_back();
    cout << directionToString(d) << " ";
  }
  cout << endl;
}
