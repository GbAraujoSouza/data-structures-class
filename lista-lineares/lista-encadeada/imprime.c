#include <stdio.h>
#include <stdlib.h>

typedef struct aux {
  int val;
  struct aux* next;
} node;

void imprime(node* head);

int main() {

  node* list = (node*)malloc(sizeof(node));
  list->val = 1;
  list->next = NULL;
  imprime(list);


  return 0;
}

void imprime(node* head) {
  node* pt = head;
  while(pt != NULL) {
    printf("%d ", pt->val);
    pt = pt->next;
  }
  puts("");
}
