#include "PacMaze.h"
#include <vector>
vector<Node*> open;
bool compare(Node* n1, Node* n2) {
  return n1->hcost > n2->hcost;
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
    } else {
      n->visited = true;
    }
  }
}

void SearchGraph::astarInsert(Node *n) {
  open.push_back(n); 
  push_heap(open.begin(),open.end());
  make_heap(open.begin(), open.end(), compare); 
}

void SearchGraph::astarInsertList(list<Node*>& l) {
  list<Node*>::const_iterator it;
  for(it = l.begin(); it != l.end(); ++it) {
    astarInsert(*it);
  }
}

Node* SearchGraph::astarRemove() {
  if(!open.empty()) {
    pop_heap(open.begin(),open.end());
    Node* n = open.back(); 
    open.pop_back();
    make_heap(open.begin(), open.end(), compare); 
    return n;
  }
  else
    return NULL;
}
