#include <stdio.h>
#include <stdlib.h>

// Red-black tree node
typedef struct n {
    int val;
    char color; // 'r' or 'b'
    struct n* left;
    struct n* right;
} treeNode;

// Stack node
typedef struct aux {
    treeNode* node;
    struct aux *next;
} stackNode;

// Stack
typedef struct stack {
    stackNode *topo;
} stack;

void preOrderPrint(treeNode* root);
void insereStack(stack *s, treeNode* node);
void popStack(stack *s, treeNode** node);
void insereRBTree(treeNode** root, int val);
void recolor(treeNode* n);
void consertaFelix(treeNode** root, treeNode* node, stack* lineage);
void freeStack(stack* s);
treeNode* rotateLeft(treeNode* root, treeNode* node);
treeNode* rotateRight(treeNode* root, treeNode* node);

void preOrderPrint(treeNode* root) {
    if (!root) return;
    printf("%d%c ", root->val, root->color);
    preOrderPrint(root->left);
    preOrderPrint(root->right);
}

void insereStack(stack *s, treeNode* node) {
    stackNode *new = (stackNode *)malloc(sizeof(stackNode));
    new->node = node;
    new->next = s->topo;
    s->topo = new;
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
        new->color = 'b'; // Root is always black
        *root = new;
        new->left = NULL;
        new->right = NULL;
    } else {
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
    if (node == root) {
        root = rightChild;
    }
    return rightChild;
}

treeNode* rotateRight(treeNode* root, treeNode* node) {
    treeNode* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    leftChild->color = node->color;
    node->color = 'r';
    if (node == root) {
        root = leftChild;
    }
    return leftChild;
}

void consertaFelix(treeNode** root, treeNode* node, stack* lineage) {
    treeNode* parent = NULL;
    treeNode* grandParent = NULL;
    treeNode* uncle = NULL;

    while (lineage->topo != NULL && lineage->topo->node->color == 'r') {
        popStack(lineage, &parent);
        popStack(lineage, &grandParent);

        if (parent == grandParent->left) {
            uncle = grandParent->right;

            if (uncle != NULL && uncle->color == 'r') { // Case 1: Uncle is red
                grandParent->color = 'r';
                parent->color = 'b';
                uncle->color = 'b';
                node = grandParent;
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
        } else { // Symmetric cases
            uncle = grandParent->left;

            if (uncle != NULL && uncle->color == 'r') { // Case 1: Uncle is red
                grandParent->color = 'r';
                parent->color = 'b';
                uncle->color = 'b';
                node = grandParent;
            } else { // Uncle is black or null
                if (node == parent->left) { // Case 2: Node is left child
                    parent = rotateRight(*root, parent);
                    node = parent->right;
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
    preOrderPrint(root);
    puts("");
    insereRBTree(&root, 1);
    preOrderPrint(root);
    puts("");

    return 0;
}
