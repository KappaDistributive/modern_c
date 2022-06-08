#include <stdint.h>
#include <stdio.h>

/* Union-Find */

#define TABLE_SIZE 20

void InitPartition(size_t parent[TABLE_SIZE]) {
  for (size_t i = 0; i < TABLE_SIZE; ++i) {
    parent[i] = SIZE_MAX;
  }
}

size_t Find(size_t element, const size_t parent[static TABLE_SIZE]) {
  /* Return the root of `element` in partition */
  size_t candidate = element;
  while (1) {
    if (parent[candidate] == SIZE_MAX) {
      return candidate;
    }
    candidate = parent[candidate];
  }
}

void FindReplace(
  size_t element,
  size_t value,
  size_t parent[static TABLE_SIZE]) {
  do {
    size_t new_element = parent[element];
    parent[element] = value;
    element = new_element;
  } while (element != SIZE_MAX);
}

void FindCompress(size_t element, size_t parent[static TABLE_SIZE]) {
  size_t root = Find(element, parent);
  while (parent[element] != SIZE_MAX) {
    size_t new_element = parent[element];
    parent[element] = root;
    element = new_element;
  }
}

void Union(size_t x, size_t y, size_t parent[static TABLE_SIZE]) {
  FindCompress(x, parent);
  size_t root = Find(x, parent);
  FindReplace(y, root, parent);
}

void PrintPartition(size_t parent[static TABLE_SIZE]) {
  printf("{");
  for (size_t i = 0; i < TABLE_SIZE; ++i) {
    if (parent[i] == SIZE_MAX) {
      printf("{");
      for (size_t j = 0; j < TABLE_SIZE; ++j) {
        if (Find(j, parent) == i) {
          printf("%zu, ", j);
        }
      }
      printf("}, ");
    }
  }
  printf("}\n");
}

int main() {
  size_t parent[TABLE_SIZE];
  InitPartition(parent);
  PrintPartition(parent);
  Union(0, 1, parent);
  PrintPartition(parent);
  Union(2, 3, parent);
  PrintPartition(parent);
  Union(0, 3, parent);
  PrintPartition(parent);
  Union(4, 6, parent);
  PrintPartition(parent);
  Union(5, 7, parent);
  PrintPartition(parent);
  Union(6, 7, parent);
  PrintPartition(parent);
  Union(0, 4, parent);
  PrintPartition(parent);
}
