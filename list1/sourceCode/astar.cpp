#include "PacMaze.h"
#include <queue>
list<Node*> open;
bool compare(Node* n1, Node* n2) {
  return n1->hcost < n2->hcost;
}
// exerc 3
void SearchGraph::astar() {
  Node* n;

  explored.clear();
  astarInsert(root);

  while(true) {
    n = astarRemove();
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
      astarInsertList(n->children);
    }
    else {
      n->visited = true;
    }
  }
}

void SearchGraph::astarInsert(Node *n) {
  open.push_back(n);
}

void SearchGraph::astarInsertList(list<Node*>& l) {
  list<Node*>::const_iterator it;
  for(it = l.begin(); it != l.end(); ++it) {
    open.push_back(*it);
  }
  open.sort(compare);
}

Node* SearchGraph::astarRemove() {
  if(!open.empty()) {
    Node* n = open.front();
    open.pop_front(); 
    return n;
  }
  else
    return NULL;
}
