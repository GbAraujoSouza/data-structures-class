#include <stdio.h>
#include <stdlib.h>
int busca1(int* arr, int x, int size);

int main() {

  int size = 5;
  int* arr = (int*)malloc(sizeof(int) * size);
  for (int i = 0; i < size; i++) {
    arr[i] = i + 1;
  }
  int cade = busca1(arr, 2, size);
  printf("%d\n", cade);

  return 0;
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
