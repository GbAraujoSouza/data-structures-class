#include <stdio.h>
#include <stdlib.h>
int remove_lista(int* arr, int x, int* size);
int busca1(int* arr, int x, int size);
void print_lista(int* arr, int size);

int main() {

  int size = 5;
  int* arr = (int*)malloc(sizeof(int) * size);
  for (int i = 0; i < size; i++) {
    arr[i] = i + 1;
  }
  print_lista(arr, size);
  remove_lista(arr, 2, &size);
  print_lista(arr, size);
  return 0;
}

int remove_lista(int* arr, int x, int* size) {
  if (!arr) return - 1;
  int removido = - 1;
  int i = busca1(arr, x, *size);
  if (i == - 1) return removido;

  removido = arr[i];
  for (int j = i; j < *size - 1; j++) {
    arr[j] = arr[j + 1];
  }
  *size = *size - 1;
  return removido;
}

int busca1(int* arr, int x, int size) {
  int busca = 0;
  int i = 0;
  while (i < size) {
    if (arr[i] == x) {
      busca = i;
      i = size + 1;
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
