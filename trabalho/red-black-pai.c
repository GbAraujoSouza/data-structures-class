#include <stdio.h>
#include <stdlib.h>

typedef struct n {
  int val;
  char color; // 'R' ou 'N'
  struct n* left;
  struct n* right;
  struct n* parent;
} treeNode;

void preOrderPrint(treeNode* root) {
  if (!root) return;
  printf("%d%c ", root->val, root->color);
  preOrderPrint(root->left);
  preOrderPrint(root->right);
}

void rotateLeft(treeNode** pRoot, treeNode* a) {
  if (!a || !a->right) return;
  treeNode* b = a->right;
  a->right = b->left;
  if (b->left) {
    b->left->parent = a;
  }
  b->parent = a->parent;
  if(!a->parent) {
    *pRoot = b;
  } else if (a == a->parent->left) {
    a->parent->left = b;
  } else {
    a->parent->right = b;
  }
  b->left = a;
  a->parent = b;
}
void rotateRight(treeNode** pRoot, treeNode* a) {
  if (!a || !a->left) return;
  treeNode* b = a->left;
  a->left = b->right;
  if (b->right) {
    b->right->parent = a;
  }
  b->parent = a->parent;
  if(!a->parent) {
    *pRoot = b;
  } else if (a == a->parent->left) {
    a->parent->left = b;
  } else {
    a->parent->right = b;
  }
  b->right = a;
  a->parent = b;
}

void consertaFelix(treeNode** pRoot, treeNode* node) {
  while (node != *pRoot && node->parent->color == 'R') {
    // treeNode* parent = node->parent;
    // treeNode* grandParent = node->parent->parent;
    if (node->parent == node->parent->parent->left) {
      treeNode* rightUncle = node->parent->parent->right;
      if (rightUncle && rightUncle->color == 'R') {
        rightUncle->color = 'N';
        node->parent->color = 'N';
        node->parent->parent->color = 'R';
        node = node->parent->parent; // proxima iteracao e feita no avo
      } else {
        if (node->parent->right == node) {
          node = node->parent;
          rotateLeft(pRoot, node);
        }
        node->parent->color = 'N';
        node->parent->parent->color = 'R';
        puts("bla");
        rotateRight(pRoot, node->parent->parent);
      }
    } else {
      treeNode* leftUncle = node->parent->parent->left;
      if (leftUncle && leftUncle->color == 'R') {
        leftUncle->color = 'N';
        node->parent->color = 'N';
        node->parent->parent->color = 'R';
        node = node->parent->parent; // proxima iteracao e feita no avo
      } else{
        if (node->parent->left == node) {
          node = node->parent;
          rotateRight(pRoot, node);
        }
        node->parent->color = 'N';
        node->parent->parent->color = 'R';
        rotateLeft(pRoot, node->parent->parent);
      }
    }
  }
  (*pRoot)->color = 'N';
}

void insertRBTree(treeNode** pRoot, int val) {
  treeNode* new = (treeNode*)malloc(sizeof(treeNode));
  new->val = val;
  new->color = 'R';
  new->left = NULL;
  new->right = NULL;
  new->parent = NULL;

  if (!*pRoot) {
    // arvore vazia
    new->color = 'N';
    *pRoot = new;
  } else {
    // descer ate o no folha
    treeNode* x = *pRoot;
    treeNode* parent = NULL;
    while (x) {
      parent = x;
      if (x->val > val) {
        x = x->left;
      } else {
        x = x->right;
      }
    }
    new->parent = parent;

    // inserir novo no
    if (new->val > parent->val) {
      parent->right = new;
    } else {
      parent->left = new;
    }

    consertaFelix(pRoot, new);
  }
}

int main() {

  treeNode* root = NULL;
  char input[100];
  while(fgets(input, 100, stdin)) {
    switch (input[0]) {
      case 'i':
        insertRBTree(&root, atoi(&input[2]));
        break;
      case 'p':
        preOrderPrint(root);
        puts("");
        break;
    }
  }
  
  return 0;
}
