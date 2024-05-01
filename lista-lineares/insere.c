#include <stdio.h>
#include <stdlib.h>
void insere_lista(int* arr, int x, int* num_elem, int* tam);
int busca1(int* arr, int x, int size);
void print_lista(int* arr, int size);
void overflow(int* arr, int* tam);

#define TAM 5

int main() {

  int tam = TAM;
  int num_elem = 0;
  int* arr = (int*)malloc(sizeof(int) * TAM);

  for (int i = 0; i < TAM; i++) {
    insere_lista(arr, i+1, &num_elem, &tam);
  }
  puts("array: ");
  print_lista(arr, num_elem);
  return 0;
}

void overflow(int* arr, int* tam) {
  int t = *tam * 2;
  arr = (int*)realloc(arr, t);
  *tam = t;
  return;
}

void insere_lista(int* arr, int x, int* num_elem, int* tam) {
  // insere um elemento no final da lista
  if (num_elem >= tam) {
    overflow(arr, tam);
  }
  if (busca1(arr, x, *num_elem) != -1) {
    puts("Elemento ja está na lista");
    return;
  }
  arr[*num_elem] = x;
  *num_elem = *num_elem + 1;
}

int busca1(int* arr, int x, int num_elem) {
  int busca = -1;
  int i = 0;
  while (i < num_elem) {
    if (arr[i] == x) {
      busca = i;
      i = num_elem + 1; // poderia usar um break; aq
    } else
      i++;
  }
  return busca;
}

void print_lista(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  puts("");
}
