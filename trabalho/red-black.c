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
  treeNode node;
  struct aux *next;
} stackNode;

typedef struct stack
{
  stackNode *topo;
} stack;

void preOrderPrint(treeNode* root) {
  // node* pt = root;
  if (!root) return;
  if (root->left != NULL) {
    preOrderPrint(root->left);
  }
  printf("%d ", root->val);
  if (root->right != NULL) {
    preOrderPrint(root->right);
  }
}

void insereStack(stack *s, treeNode node)
{
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

void popStack(stack *s, treeNode* node)
{
  if (s->topo != NULL)
  {
    *node = s->topo->node;
    stackNode *tmp = s->topo;
    s->topo = s->topo->next;
    free(tmp);
  }
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
    while (x) {
      insereStack(lineage, *x);
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
    stackNode* n = lineage->topo;
    while (n) {
      printf("%d%c\n", n->node.val, n->node.color);
      n = n->next;
    }
    puts("");
  }
}

void recolor(treeNode** n) {
  (*n)->color = ((*n)->color == 'r') ? 'b' : 'r';
}

void consertaFelix(treeNode* node, stack* lineage) {
  treeNode* parent = NULL;
  treeNode* grandParent = NULL;
  popStack(lineage, parent);
  popStack(lineage, grandParent);
  // caso taiz
  if (!parent) {
    return;
  } else if (!grandParent) {
    // no pai é raiz
    if (parent->color == 'r')
      recolor(&parent);
  }
}

int main() {

  treeNode* root = NULL;
  insereRBTree(&root, 10);
  insereRBTree(&root, 2);
  insereRBTree(&root, 39);
  insereRBTree(&root, 5);
  insereRBTree(&root, 1);

  preOrderPrint(root);
  
  return 0;
}
