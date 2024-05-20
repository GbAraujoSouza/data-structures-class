#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void free_stack(stack* s) {
  while(s->topo != NULL) {
    node* tmp = s->topo;
    s->topo = s->topo->next;
    free(tmp);
  }
  free(s);
}

int isOperator(char c) {

}

int main(int argc, char *argv[])
{
  stack* nums = (stack*)malloc(sizeof(stack));
  nums->topo = NULL;

  stack* operations = (stack*)malloc(sizeof(stack));
  operations->topo = NULL;

  char exp[100];
  fgets(exp, 100, stdin);

  for (int i = 0; i < strlen(exp); i++) {
    if (isdigit(exp[i])) {
      int n = atoi(&exp[i]);
      insere(nums, n);
      while (isdigit(exp[i])) {
        i++;
      }
    }
    else if(isOperator(exp[i])) {

    }
  }



  return 0;
}
