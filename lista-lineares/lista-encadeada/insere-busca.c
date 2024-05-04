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

void insere(list* list, int val) {
  // insere um elemento ainda nao existente na lista (aqui a lista é um conjunto - sem repetição)
  node* ant;
  node* pont;
  busca(list, &ant, &pont, val);
  if (pont == NULL) {
    node* new = (node*)malloc(sizeof(node));
    new->chave = val;
    new->next = NULL;

    if (ant == NULL)
      list->head.next = new;
    else
      ant->next = new;

    return;
  } 
  printf("Elemento %d ja consta na lista\n", val);
}

void remove_lista(list* list, int val) {
  node* ant;
  node* pont;
  busca(list, &ant, &pont, val);
  
  if (pont != NULL) {
    if (pont == list->head.next) {
      // elemento a ser removido e o primeiro da lista
      list->head.next = pont->next;
      free(pont);
    } else {
      ant->next = pont->next;
      free(pont);
    }
  } else {
    printf("Elemento %d nao consta na lista\n", val);
  }
}

int main() {

  list* l = malloc(sizeof(list));
  l->head.next = NULL;
  for (int i = 0; i < 10; i++) {
    insere(l, i+1);
  }
  remove_lista(l, 11);
  imprime(l);

  return 0;
}

