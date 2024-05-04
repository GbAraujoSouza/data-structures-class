#include <stdio.h>
#include <stdlib.h>

typedef struct aux {
  int val;
  struct aux* next;
}node;

typedef struct queue {
  node* inicio;
  node* fim;
}queue;

void print_queue(queue* q) {
  node* pt = q->inicio;
  while (pt != NULL) {
    printf("%d ", pt->val);
    pt = pt->next;
  }
  puts("");

}

void enqueue(queue* q, int val) {
  node* new = (node*)malloc(sizeof(queue));
  new->val = val;
  new->next = NULL;
  if (q->inicio == NULL) {
    q->inicio = new;
    q->fim = new;
    return;
  }
  q->fim->next = new;
  q->fim = new;
}

void dequeue(queue* q) {
  node* pt = q->inicio;
  if (pt != NULL) {
    q->inicio = q->inicio->next;
    free(pt);
  }
  if (q->inicio == NULL) {
    q->fim = q->inicio;
  }
}


int main(int argc, char *argv[])
{
  queue* q = (queue*)malloc(sizeof(queue));
  q->fim = NULL;
  q->inicio = NULL;

  int i = 0;
  while (i < 10) {
    enqueue(q, i+1);
    i++;
  }
  dequeue(q);
  
  print_queue(q);

  return EXIT_SUCCESS;
}

