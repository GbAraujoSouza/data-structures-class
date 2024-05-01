#include <stdlib.h>
#include <stdio.h>

struct ListNode {
  int val;
  struct ListNode *next;
};
typedef struct ListNode node;
// signatures
void append(node** list, int x);
node* mergeTwoLists(struct ListNode* list1, struct ListNode* list2);
void printList(node* list);
// Definition for singly-linked list.

int main() {

  // node* n = (node*)malloc(sizeof(node));
  node* n = NULL;

  // append(&n, 1);
  // append(&n, 2);
  // append(&n, 3);
  // append(&n, 4);
  printList(n);

  node* n2 = (node*)malloc(sizeof(node));
  // node* n2 = NULL;

  // append(&n2, 1);
  // append(&n2, 2);
  // append(&n2, 3);
  // append(&n2, 4);
  // append(&n2, 5);
  // append(&n2, 5);
  printList(n2);

  node* res = mergeTwoLists(n, n2);

  printList(res);


  return 0;
}

node* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
  node* pt1 = list1;
  node* pt2 = list2;
  node* result = NULL;
  while(pt1 != NULL && pt2 != NULL) {
    if (pt1->val <= pt2->val) {
      append(&result, pt1->val);
      pt1 = pt1->next;
    } else {
      append(&result, pt2->val);
      pt2 = pt2->next;
    }
  }
  // append remaining list
  while(pt1 != NULL) {
    append(&result, pt1->val);
    pt1 = pt1->next;
  }
  while(pt2 != NULL) {
    append(&result, pt2->val);
    pt2 = pt2->next;
  }
  return result;
}

void append(node** list, int x) {
  node* new = (node*)malloc(sizeof(node));
  if (!new) return;
  new->val = x;
  new->next = NULL;

  if (*list == NULL) {
    *list = new;
    return;
  }

  node* current = *list;
  if (!current) return;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = new;
}

void printList(node* list) {
  node* pt = list;
  while(pt != NULL) {
    printf("%d ", pt->val);
    pt = pt->next;
  }
  puts("");
}

