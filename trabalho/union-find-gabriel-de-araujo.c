#include <stdio.h>
#include <stdlib.h>

typedef struct Set {
  int parent;
  int size;
}Set;

int find(Set subsets[], int i) {
  if (subsets[i].parent != i) {
    subsets[i].parent = find(subsets, subsets[i].parent);
  }
  return subsets[i].parent;
}

void unionSets(Set subsets[], int x, int y) {
  int xroot = find(subsets, x);
  int yroot = find(subsets, y);

  if (xroot == yroot) {
    return;
  }

  if (subsets[xroot].size <= subsets[yroot].size) {
    subsets[xroot].parent = yroot;
    subsets[yroot].size += subsets[xroot].size;
  } else if (subsets[xroot].size > subsets[yroot].size) {
    subsets[yroot].parent = xroot;
    subsets[xroot].size += subsets[yroot].size;
  }
}

Set* createSubsets(int n) {
  Set* subsets = (Set*)malloc(n * sizeof(Set));
  for (int i = 0; i < n; i++) {
    subsets[i].parent = i;
    subsets[i].size = 1;
  }
  return subsets;
}

int findMaxSets(Set subsets[], int n) {
  int max = 0;
  for (int i = 0; i < n; i++) {
    if (subsets[i].size > max)
      max = subsets[i].size;
  }
  return max;
}

int main() {
  
  int tests;
  scanf("%d", &tests);
  while (tests != 0) {
    int n, m;
    scanf("%d %d", &n, &m);
    // criar grupos
    Set* subsets = createSubsets(n);
    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d %d", &a, &b);
      unionSets(subsets, a-1, b-1);
    }
    printf("%d\n", findMaxSets(subsets, n));
    tests--;
  }

  return 0;
}
