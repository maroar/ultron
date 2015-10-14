#include "PacMaze.h"
// exerc 3
void SearchGraph::bfs() {
  Node* n;

  explored.clear();
  bfsInsert(root);

  while(true) {
    n = bfsRemove();
    if(!n) {
      cout << "No Solution" << endl;
      return;
    }

    if(nodeIsGoal(n)) {
      return solution(n);
      //return printDot();
    }

    if(!alreadyVisited(n->r, n->c)) {
      n->expand();
      bfsInsertList(n->children);
    }
  }
}

void SearchGraph::bfsInsert(Node *n) {
  fringe.push_back(n);
}

void SearchGraph::bfsInsertList(list<Node*>& l) {
  list<Node*>::const_iterator it;
  for(it = l.begin(); it != l.end(); ++it) {
    fringe.push_back(*it);
  }
}

Node* SearchGraph::bfsRemove() {
  if(!fringe.empty()) {
    Node* n = fringe.front();
    fringe.pop_front(); 
    return n;
  }
  else
    return NULL;
}
