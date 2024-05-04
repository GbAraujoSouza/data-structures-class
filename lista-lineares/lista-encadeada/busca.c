#include <stdlib.h>
#include <stdio.h>

typedef struct aux {
  int chave;
  struct aux* next;
} node;

typedef struct lista {
  node head;
} list;

void busca(list* list, node** ant, node** pont, int val) {
  *pont = NULL;
  *ant = list->head.next;
  node* pt = list->head.next;

  while(pt != NULL) {
    if (pt->chave < val) {
      // avabcar
      *ant = pt;
      pt = pt->next;
    } else if (pt->chave == val) {
      *pont = pt;
      pt = NULL; // out break;
    }
  }
}

void imprime(list* list) {
  node* pt = list->head.next;
  while (pt != NULL) {
    printf("%d ", pt->chave);
    pt = pt->next;
  }
  puts("");
}

void append(list* list, int val) {
  node* new = (node*)malloc(sizeof(node));
  new->chave = val;
  new->next = NULL;
  node* pt = list->head.next;
  if (pt == NULL) {
    list->head.next = new;
    return;
  }
  while (pt->next != NULL) {
    pt = pt->next;
  }
  pt->next = new;

}

int main() {

  list* l = malloc(sizeof(list));
  l->head.next = NULL;
  for (int i = 0; i < 10; i++) {
    append(l, i+1);
  }
  node* anterior = NULL;
  node* pont = NULL;
  busca(l, &anterior, &pont, 10);
  if (anterior == NULL) puts("deu ruim anterior");
  if (pont == NULL) {
    puts("Valor nao encontrado");
    printf("Ultimo valor: %d\n", anterior->chave);
  } else {
    puts("Valor encontrado");
    printf("Anterior: %d\n", anterior->chave);
  }

  return 0;
}
