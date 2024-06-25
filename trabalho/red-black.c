#include <stdio.h>
#include <stdlib.h>

// arvore rubro negra
typedef struct n {
  int val;
  char color; // 'r' ou 'b'
  struct n* left;
  struct n* right;
} treeNode;

// pilha
typedef struct aux
{
  treeNode* node;
  struct aux *next;
} stackNode;

typedef struct stack
{
  stackNode *topo;
} stack;

void preOrderPrint(treeNode* root);
void consertaFelix(treeNode** root, treeNode* node, stack* lineage);
void insereStack(stack *s, treeNode* node);
void popStack(stack *s, treeNode** node);
void insereRBTree(treeNode** root, int val);
void recolor(treeNode* n);
treeNode* rotateRight(treeNode* root, treeNode* node);
treeNode* rotateRight(treeNode* root, treeNode* node);
void freeStack(stack* s);

void preOrderPrint(treeNode* root) {
  // node* pt = root;
  if (!root) return;
  if (root->left != NULL) {
    preOrderPrint(root->left);
  }
  printf("%d%c ", root->val, root->color);
  if (root->right != NULL) {
    preOrderPrint(root->right);
  }
}

void insereStack(stack *s, treeNode* node) {
  stackNode *new = (stackNode *)malloc(sizeof(stackNode));
  new->node = node;

  if (s->topo == NULL)
  {
    s->topo = new;
    new->next = NULL;
  }
  else
  {
    new->next = s->topo;
    s->topo = new;
  }
}

void popStack(stack *s, treeNode** node) {
  if (s->topo != NULL) {
    *node = s->topo->node;
    stackNode *tmp = s->topo;
    s->topo = s->topo->next;
    free(tmp);
  }
}

void freeStack(stack* s) {
  treeNode* tmp;
  while (s->topo != NULL) {
    popStack(s, &tmp);
  }
  free(s);
}

void insereRBTree(treeNode** root, int val) {
  if (*root == NULL) {
    treeNode* new = (treeNode*)malloc(sizeof(treeNode));
    new->val = val;
    new->color = 'r';
    *root = new;
    new->left = NULL;
    new->right = NULL;
  }
  else {
    treeNode* x = *root;
    treeNode* parent = NULL;
    stack* lineage = (stack*)malloc(sizeof(stack));
    lineage->topo = NULL;
    while (x) {
      insereStack(lineage, x);
      parent = x;
      if (x->val > val) {
        x = x->left;
      } else {
        x = x->right;
      }
    }
    treeNode* new = (treeNode*)malloc(sizeof(treeNode));
    new->val = val;
    new->color = 'r';
    new->left = NULL;
    new->right = NULL;
    if (parent->val > val) {
      parent->left = new;
    } else {
      parent->right = new;
    }
    insereStack(lineage, new);
    consertaFelix(root, new, lineage);
    freeStack(lineage);
  }
}

void recolor(treeNode* n) {
  n->color = (n->color == 'r') ? 'b' : 'r';
}

treeNode* rotateLeft(treeNode* root, treeNode* node) {
  treeNode* rightChild = node->right;
  node->right = rightChild->left;
  rightChild->left = node;
  rightChild->color = node->color;
  node->color = 'r';
  return rightChild;
}

treeNode* rotateRight(treeNode* root, treeNode* node) {
  treeNode* leftChild = node->left;
  node->left = leftChild->right;
  leftChild->right = node;
  leftChild->color = node->color;
  node->color = 'r';
  return leftChild;
}

void consertaFelix(treeNode** root, treeNode* node, stack* lineage) {
  treeNode* parent = NULL;
  treeNode* grandParent = NULL;
  while (lineage->topo != NULL && lineage->topo->node->color == 'r') {

    popStack(lineage, &parent);
    popStack(lineage, &grandParent);
    if (parent == NULL) {
      return;
    } else if (!grandParent) {
      if (parent->color == 'r') {
        recolor(parent);
      }
    } else if (parent->color == 'b') {
      return;
    } else {
      if (grandParent->left == parent) {
        if (grandParent->right && grandParent->right->color == 'r') {
          recolor(parent);
          recolor(grandParent->right);
          recolor(grandParent);
          node = grandParent;
        }
      } else if (grandParent->right == parent) {
        if (grandParent->left && grandParent->left->color == 'r') {
          recolor(parent);
          recolor(grandParent->left);
          recolor(grandParent);
          node = grandParent;
        } else {
          if (node == parent->left) { // Case 2: Node is left child
            parent = rotateRight(*root, parent);
            node = parent->right;
          } else { // Uncle is black or null
            if (node == parent->right) { // Case 2: Node is right child
              parent = rotateLeft(*root, parent);
              node = parent->left;
            }
            // Case 3: Node is left child
            grandParent->left = rotateRight(*root, grandParent);
            recolor(grandParent);
            recolor(grandParent->left);
            if (lineage->topo == NULL) {
              *root = grandParent->left;
            }
          }
          // Case 3: Node is right child
          grandParent->right = rotateLeft(*root, grandParent);
          recolor(grandParent);
          recolor(grandParent->right);
          if (lineage->topo == NULL) {
            *root = grandParent->right;
          }
        }
      }
    }
  }
  (*root)->color = 'b';
}

int main() {

  treeNode* root = NULL;
  insereRBTree(&root, 10);
  preOrderPrint(root);
  puts("");
  insereRBTree(&root, 2);
  preOrderPrint(root);
  puts("");
  insereRBTree(&root, 39);
  preOrderPrint(root);
  puts("");
  insereRBTree(&root, 5);
  insereRBTree(&root, 1);

  preOrderPrint(root);
  
  return 0;
}
