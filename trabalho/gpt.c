#include <stdio.h>
#include <stdlib.h>

// Red-black tree node
typedef struct n {
    int val;
    char color; // 'r' or 'b'
    struct n* left;
    struct n* right;
} treeNode;

void preOrderPrint(treeNode* root) {
    if (!root) return;
    preOrderPrint(root->left);
    printf("%d%c ", root->val, root->color);
    preOrderPrint(root->right);
}
treeNode* rotateLeft(treeNode *root) {
    treeNode *rightChild = root->right;
    root->right = rightChild->left;
    rightChild->left = root;
    return rightChild;
}
treeNode* rotateRight(treeNode *root) {
    treeNode *leftChild = root->left;
    root->left = leftChild->right;
    leftChild->right = root;
    return leftChild;
}

treeNode* fixViolations(treeNode *root) {
  if (root->left && root->left->color == 'r') {
    if (root->left->left && root->left->left->color == 'r') {
      // Right rotate needed
      root = rotateRight(root);
      root->color = 'b';
      root->right->color = 'r';
    } else if (root->left->right && root->left->right->color == 'r') {
      // Left-right rotate needed
      root->left = rotateLeft(root->left);
      root = rotateRight(root);
      root->color = 'b';
      root->right->color = 'r';
    }
  } else if (root->right && root->right->color == 'r') {
    if (root->right->right && root->right->right->color == 'r') {
      // Left rotate needed
      root = rotateLeft(root);
      root->color = 'b';
      root->left->color = 'r';
    } else if (root->right->left && root->right->left->color == 'r') {
      // Right-left rotate needed
      root->right = rotateRight(root->right);
      root = rotateLeft(root);
      root->color = 'b';
      root->left->color = 'r';
    }
  }
  return root;
}

void insertRBTree(treeNode** rootRef, int val) {
  if (*rootRef == NULL) {
    treeNode* new = (treeNode*)malloc(sizeof(treeNode));
    new->val = val;
    new->color = 'r';
    new->left = NULL;
    new->right = NULL;
    *rootRef = new;
    // (*rootRef)->color = 'b'; // root must be black
    return;
  }

  treeNode* root = *rootRef;

  if (val < root->val) {
    insertRBTree(&root->left, val);
  } else if (val > root->val) {
    insertRBTree(&root->right, val);
  }

  if (root->color == 'b') {
    if ((root->left && root->left->color == 'r') && (root->right && root->right->color == 'r')) {
      root->left->color = 'b';
      root->right->color = 'b';
      root->color = 'r';
    } else {
      *rootRef = fixViolations(root);
    }
  } else {
    *rootRef = fixViolations(root);
  }
}
// void insereRBTree(treeNode** root, int val) {
//   if (*root == NULL) {
//     treeNode* new = (treeNode*)malloc(sizeof(treeNode));
//     new->val = val;
//     new->color = 'b'; // Root is always black
//     *root = new;
//     new->left = NULL;
//     new->right = NULL;
//   } else {
//     treeNode* x = *root;
//     treeNode* parent = NULL;
//     stack* lineage = (stack*)malloc(sizeof(stack));
//     lineage->topo = NULL;
//     while (x) {
//       insereStack(lineage, x);
//       parent = x;
//       if (x->val > val) {
//         x = x->left;
//       } else {
//         x = x->right;
//       }
//     }
//     treeNode* new = (treetreeNode*)malloc(sizeof(treetreeNode));
//     new->val = val;
//     new->color = 'r';
//     new->left = NULL;
//     new->right = NULL;
//     if (parent->val > val) {
//       parent->left = new;
//     } else {
//       parent->right = new;
//     }
//     insereStack(lineage, new);
//     consertaFelix(root, new, lineage);
//     freeStack(lineage);
//   }
// }
//
// void recolor(treeNode* n) {
//     n->color = (n->color == 'r') ? 'b' : 'r';
// }
//
// treeNode* rotateLeft(treetreeNode* root, treetreeNode* node) {
//     treeNode* rightChild = node->right;
//     node->right = rightChild->left;
//     rightChild->left = node;
//     rightChild->color = node->color;
//     node->color = 'r';
//     if (node == root) {
//         root = rightChild;
//     }
//     return rightChild;
// }
//
// treeNode* rotateRight(treetreeNode* root, treetreeNode* node) {
//     treeNode* leftChild = node->left;
//     node->left = leftChild->right;
//     leftChild->right = node;
//     leftChild->color = node->color;
//     node->color = 'r';
//     if (node == root) {
//         root = leftChild;
//     }
//     return leftChild;
// }
//
// void consertaFelix(treeNode** root, treetreeNode* node, stack* lineage) {
//     treeNode* parent = NULL;
//     treeNode* grandParent = NULL;
//     treeNode* uncle = NULL;
//
//     while (lineage->topo != NULL && lineage->topo->node->color == 'r') {
//         popStack(lineage, &parent);
//         popStack(lineage, &grandParent);
//
//         if (parent == grandParent->left) {
//             uncle = grandParent->right;
//
//             if (uncle != NULL && uncle->color == 'r') { // Case 1: Uncle is red
//                 grandParent->color = 'r';
//                 parent->color = 'b';
//                 uncle->color = 'b';
//                 node = grandParent;
//             } else { // Uncle is black or null
//                 if (node == parent->right) { // Case 2: treeNode is right child
//                     parent = rotateLeft(*root, parent);
//                     node = parent->left;
//                 }
//                 // Case 3: treeNode is left child
//                 grandParent->left = rotateRight(*root, grandParent);
//                 recolor(grandParent);
//                 recolor(grandParent->left);
//                 if (lineage->topo == NULL) {
//                     *root = grandParent->left;
//                 }
//             }
//         } else { // Symmetric cases
//             uncle = grandParent->left;
//
//             if (uncle != NULL && uncle->color == 'r') { // Case 1: Uncle is red
//                 grandParent->color = 'r';
//                 parent->color = 'b';
//                 uncle->color = 'b';
//                 node = grandParent;
//             } else { // Uncle is black or null
//                 if (node == parent->left) { // Case 2: treeNode is left child
//                     parent = rotateRight(*root, parent);
//                     node = parent->right;
//                 }
//                 // Case 3: treeNode is right child
//                 grandParent->right = rotateLeft(*root, grandParent);
//                 recolor(grandParent);
//                 recolor(grandParent->right);
//                 if (lineage->topo == NULL) {
//                     *root = grandParent->right;
//                 }
//             }
//         }
//     }
//     (*root)->color = 'b';
// }
//
int main() {
    treeNode* root = NULL;
    insertRBTree(&root, 10);
    preOrderPrint(root);
    puts("");
    insertRBTree(&root, 20);
    preOrderPrint(root);
    puts("");
    insertRBTree(&root, 30);
    preOrderPrint(root);
    puts("");
    insertRBTree(&root, 40);
    preOrderPrint(root);
    puts("");
    insertRBTree(&root, 50);
    preOrderPrint(root);
    puts("");

    return 0;
}
