#include <stdio.h>
#include <stdlib.h>

typedef struct n {
  int val;
  struct n* left;
  struct n* right;
} node;

typedef struct BinaryTree {
  node root;
} BinaryTree;

void preOrderPrint(node* root) {
  // node* pt = root;
  if (!root) return;
  printf("%d ", root->val);
  if (root->left != NULL) {
    preOrderPrint(root->left);
  }
  if (root->right != NULL) {
    preOrderPrint(root->right);
  }
}

void insere(node** root, int val) {
  if (*root == NULL) {
    node* new = (node*)malloc(sizeof(node));
    new->val = val;
    *root = new;
    new->left = NULL;
    new->right = NULL;
  }
  else {
    if (val > (*root)->val) {
      insere(&((*root)->right), val);
    }
    else if (val <= (*root)->val) {
      insere(&((*root)->left), val);
    }
  }
}

node* removeTree(node** root, int val) {
  node* x = *root;
  if (!x) {
    return x;
  }

  if (val == x->val) {
    // encontramos o no a ser removido
    if (!x->right && !x->left) {
      // no folha
      free(x);
      return NULL;
    }
    else if(!x->right || !x->left) {
      // no com 1 filho
      node* aux;
      if (x->right) 
        aux = x->right;
      else {
        aux = x->left;
      }
      free(x);
      return aux;
    }
    else {
      // no com dois filhos
      node* minNode = x->right;
      while(minNode->left) {
        minNode = minNode->left;
      }
      x->val = minNode->val;
      minNode->val = val;
      x->right = removeTree(&x->right, val);
    }
  }
  else if (val < x->val) {
    x->left = removeTree(&x->left, val);
  }
  else {
    x->right = removeTree(&x->right, val);
  }

  return x;

}

int main(int argc, char *argv[])
{
  node* root = NULL;
  char input[10];
  while(!feof(stdin)) {
    fgets(input, 10, stdin);
    switch (input[0]) {
      case 'i':
        insere(&root, atoi(&input[2]));
        break;
      case 'p':
        preOrderPrint(root);
        puts("");
        break;
      case 'r':
        removeTree(&root, atoi(&input[2]));
        break;
    }
  }

  return 0;
}
