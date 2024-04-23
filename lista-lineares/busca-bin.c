#include <stdio.h>
#include <stdlib.h>
int busca_bin(int* arr, int x, int ini, int end);

int main() {

  int size = 5;
  int* arr = (int*)malloc(sizeof(int) * size);
  for (int i = 0; i < size; i++) {
    arr[i] = i + 1;
  }
  int cade = busca_bin(arr, 6, 0, size-1);
  printf("%d\n", cade);

  return 0;
}

int busca_bin(int* arr, int x, int ini, int end) {
  if (ini > end) {
    return -1;
  }
  int mid = (ini + end) / 2;
  if (arr[mid] > x) {
    busca_bin(arr, x, ini, mid);
  } else if (arr[mid] < x) {
    busca_bin(arr, x, mid+1, end);
  } else if (arr[mid] == x){
    return mid;
  }
}
