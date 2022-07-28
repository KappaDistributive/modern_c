#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_sorted(size_t size, const double array[size]) {
  for (size_t i = 1; i < size; ++i) {
    if (array[i] < array[i - 1]) {
      return false;
    }
  }
  return true;
}

void merge_sort_step(size_t lower, size_t upper, double a[], double aux[]) {
  if (upper <= lower)
    return;

  size_t mid = (upper + lower) / 2;

  merge_sort_step(lower, mid, a, aux);
  merge_sort_step(mid + 1, upper, a, aux);

  size_t index_lhs = lower;
  size_t index_rhs = mid + 1;
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

void merge_sort(size_t size, double a[size]) {
  if (size == 0)
    return;
  double *aux = (double *)malloc(sizeof(double) * size);
  merge_sort_step(0, size - 1, a, aux);
  free(aux);
}

void quick_sort_step(size_t lower, size_t upper, double a[], double smaller[],
                     double greater[]) {
  if (upper <= lower)
    return;

  double pivot = a[lower];
  size_t smaller_index = 0;
  size_t greater_index = 0;

  for (size_t index = lower; index <= upper; ++index) {
    if (a[index] < pivot) {
      smaller[smaller_index++] = a[index];
    } else {
      greater[greater_index++] = a[index];
    }
  }

  size_t index = lower;
  for (size_t i = 0; i < smaller_index; ++i) {
    a[index++] = smaller[i];
  }
  for (size_t i = 0; i < greater_index; ++i) {
    a[index++] = greater[i];
  }

  quick_sort_step(lower, lower + smaller_index, a, smaller, greater);
  quick_sort_step(lower + smaller_index + 1, upper, a, smaller, greater);
}

void quick_sort(size_t size, double a[size]) {
  if (size == 0)
    return;
  double *smaller = (double *)malloc(sizeof(double) * size);
  double *greater = (double *)malloc(sizeof(double) * size);
  quick_sort_step(0, size - 1, a, smaller, greater);
  free(smaller);
  free(greater);
}

int main(int argc, char *argv[argc + 1]) {
  double *array = (double *)malloc(sizeof(double) * (argc - 1));
  for (size_t i = 0; i < argc - 1; ++i) {
    array[i] = strtod(argv[i + 1], NULL);
    printf("%g\n", array[i]);
  }
  puts("Sorting...");
  /* merge_sort(argc - 1, array); */
  quick_sort(argc - 1, array);

  for (size_t i = 0; i < argc - 1; ++i) {
    printf("%g\n", array[i]);
  }
  assert(is_sorted(argc - 1, array));
  free(array);
  return EXIT_SUCCESS;
}
