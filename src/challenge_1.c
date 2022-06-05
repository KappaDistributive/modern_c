#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

bool is_sorted(double* array, int size) {
  for (int i = 1; i < size; ++i) {
    if (array[i] < array[i-1]) {
      return false;
    }
  }
  return true;
}

void merge_sort_step(int lower, int upper, double a[], double aux[]) {
  if (upper <= lower) return;

  int mid = (upper + lower) / 2;

  merge_sort_step(lower, mid, a, aux);
  merge_sort_step(mid + 1, upper, a, aux);
  
  int index_lhs = lower;
  int index_rhs = mid + 1;
  for (int index = lower; index <= upper; ++index) {
    if (index_lhs == mid + 1) {
      aux[index] = a[index_rhs++];
    } else if (index_rhs == upper + 1) {
      aux[index] = a[index_lhs++];
    } else if (a[index_lhs] < a[index_rhs]) {
      aux[index] = a[index_lhs++];
    } else {
      aux[index] = a[index_rhs++];
    }
  }

  for (int index = lower; index <= upper; ++index) {
    a[index] = aux[index];
  }
}

void merge_sort(double a[], int size) {
  if (size <= 0) return;
  double* aux = malloc(sizeof(double) * size);
  merge_sort_step(0, size - 1, a, aux);
  free(aux);
}


int main(int argc, char* argv[argc + 1]) {
  double* array = malloc(sizeof(double) * (argc - 1));
  for(int i = 0; i < argc - 1; ++i) {
    array[i] = strtod(argv[i + 1], NULL);
    printf("%g\n", array[i]);
  }
  puts("Sorting...");
  merge_sort(array, argc - 1);
  for(int i = 0; i < argc - 1; ++i) {
    printf("%g\n", array[i]);
  }
  free(array);
  return EXIT_SUCCESS;
}
