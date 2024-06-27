#include <stdio.h>
#include <stdlib.h>

// A structure to represent a subset for union-find
struct Subset {
  int parent;
  int size;
};

// A utility function to find the set of an element i (uses path compression technique)
int find(struct Subset subsets[], int i) {
  // find root and make root as parent of i (path compression)
  if (subsets[i].parent != i) {
    subsets[i].parent = find(subsets, subsets[i].parent);
  }
  return subsets[i].parent;
}

// A function that does union of two sets of x and y (uses union by rank)
void unionSets(struct Subset subsets[], int x, int y) {
  int xroot = find(subsets, x); // 2
  int yroot = find(subsets, y); // 6

  // Attach smaller rank tree under root of high rank tree
  if (subsets[xroot].size <= subsets[yroot].size) {
    subsets[xroot].parent = yroot;
    subsets[yroot].size += subsets[xroot].size;
  } else if (subsets[xroot].size > subsets[yroot].size) {
    subsets[yroot].parent = xroot;
    subsets[xroot].size += subsets[yroot].size;
  }
}

// Creates n sets (one for each element)
struct Subset* createSubsets(int n) {
  struct Subset* subsets = (struct Subset*)malloc(n * sizeof(struct Subset));
  for (int i = 0; i < n; i++) {
    subsets[i].parent = i;
    subsets[i].size = 1;
  }
  return subsets;
}

// A utility function to print the array of subsets
void printSubsets(struct Subset subsets[], int n) {
  for (int i = 0; i < n; i++) {
    printf("Element: %d, Parent: %d, Size: %d\n", i, subsets[i].parent, subsets[i].size);
  }
}

int main() {
  int n = 5;
  struct Subset* subsets = createSubsets(n);

  unionSets(subsets, 0, 2);
  unionSets(subsets, 4, 2);
  unionSets(subsets, 3, 1);

  printf("Find(4): %d\n", find(subsets, 4));
  printf("Find(3): %d\n", find(subsets, 3));

  printSubsets(subsets, n);

  free(subsets);

  return 0;
}
