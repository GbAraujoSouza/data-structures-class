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

void inOrderPrint(node* root) {
  // node* pt = root;
  printf("%d ", root->val);
  if (root->left != NULL) {
    inOrderPrint(root->left);
  }
  if (root->right != NULL) {
    inOrderPrint(root->right);
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

node* busca(node* root, int val) {
  if (root) {
    if (root->val > val)
      return busca(root->left, val);
    else if (root->val < val)
      return busca(root->right, val);
    else
      return root;
  }
  return NULL;
}

int busca_nivel(node** root, int x, int nivel) {
  if (*root == NULL)
    return nivel;
  if ((*root)->val == x)
    return nivel;
  if ((*root)->val < x){
    return busca_nivel(&((*root)->right), x, nivel + 1);
  }
  else {
    return busca_nivel(&((*root)->left), x, nivel+1);
  }
}

void remove_tree(node** root, int val) {
  node* x = *root;
  if (!x) {
    *root = NULL;
    return;
  }
  node* parent = NULL;
  while(x) {
    if (val < x->val) {
      parent = x; 
      x = x->left;
    } else if (val > x->val) {
      parent = x; 
      x = x->right;
    } else {
      break;
    }
  }

  if (!x) return; // valor a ser removido nao encontrado
  // no folha
  if (!x->right && !x->left) {
    if (parent->right == x)
      parent->right = NULL;
    else
      parent->left = NULL;
    free(x);
  }
  // no com apenas um filho
  else if (!x->right || !x->left) {
    if (!x->left) {
      if (parent->right == x)
        parent->right = x->right;
      else
        parent->left = x->right;
    }
    else {
      if (parent->right == x)
        parent->right = x->left;
      else
        parent->left = x->left;
    }
  }

}

int main(int argc, char *argv[])
{
  node* root = NULL;
  // int i = 0;
  // while(i < 10) {
  //   insere(&root, i+1);
  //   i++;
  // }
  insere(&root, 2);
  insere(&root, 1);
  insere(&root, 3);
  insere(&root, 0);
  
  inOrderPrint(root);
  puts("");

  remove_tree(&root, 1);

  inOrderPrint(root);
  puts("");

  return EXIT_SUCCESS;
}
