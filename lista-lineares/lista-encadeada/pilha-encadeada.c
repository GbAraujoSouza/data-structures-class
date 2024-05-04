#include <stdio.h>
#include <stdlib.h>

typedef struct aux {
  int val;
  struct aux* next;
}node;

typedef struct stack {
  node* topo;
}stack;

void insere(stack* s, int val) {
  node* new = (node*)malloc(sizeof(malloc));
  new->val = val;

  if (s->topo == NULL) {
    s->topo = new;
    new->next = NULL;
  } else {
    new->next = s->topo;
    s->topo = new;
  }
}

void pop_stack(stack* s, int* r) {
  if (s->topo != NULL) {
    *r = s->topo->val;
    node* tmp = s->topo;
    s->topo = s->topo->next;
    free(tmp);
  }
}


void print_stack(stack* s) {
  node* pt = s->topo;
  while (pt != NULL) {
    printf("%d ", pt->val);
    pt = pt->next;
  }
  puts("");
}

int main(int argc, char *argv[])
{
  stack* s = (stack*)malloc(sizeof(stack));
  s->topo = NULL;

  int i = 0;
  while (i < 10) {
    insere(s, i+1);
    i++;
  }
  int r;
  pop_stack(s, &r);
  print_stack(s);
  printf("Valor removido: %d\n", r);

  return EXIT_SUCCESS;
}
