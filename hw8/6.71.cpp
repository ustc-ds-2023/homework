#include <iostream>

struct CSTreeNode {
  char val = '\0';
  CSTreeNode *first_child = nullptr;
  CSTreeNode *next_sibling = nullptr;
};

void PrintCSTree(CSTreeNode *root, int indent = 0) {
  if (root == nullptr) {
    return;
  }
  for (int i = 0; i < indent; i++) {
    std::cout << "    ";
  }
  std::cout << root->val << std::endl;
  PrintCSTree(root->first_child, indent + 1);
  PrintCSTree(root->next_sibling, indent);
}

int main() {
  CSTreeNode *A = new CSTreeNode{'A'};
  CSTreeNode *B = new CSTreeNode{'B'};
  CSTreeNode *C = new CSTreeNode{'C'};
  CSTreeNode *D = new CSTreeNode{'D'};
  CSTreeNode *E = new CSTreeNode{'E'};
  CSTreeNode *F = new CSTreeNode{'F'};
  CSTreeNode *G = new CSTreeNode{'G'};
  A->first_child = B;
  B->next_sibling = C;
  B->first_child = E;
  C->next_sibling = D;
  C->first_child = G;
  E->next_sibling = F;
  PrintCSTree(A);
}
