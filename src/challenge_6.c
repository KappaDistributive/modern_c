#include <assert.h>
#include <stdio.h>

double vector_to_vector_product(double x[], double y[], size_t size) {
  if (size == 0) {
    return 0;
  }
  double result = 0.0;
  for (size_t i = 0; i < size; ++i) {
    result += x[i] * y[i];
  }

  return result;
}

int main() {
  double x[] = {1, 2, 3};
  double y[] = {4, 5, 6};
  printf("x = (");
  for(size_t i = 0; i < sizeof(x) / sizeof(x[0]); ++i) {
    printf("%g, ", x[i]);
  }
  printf(")\n");

  printf("y = (");
  for(size_t i = 0; i < sizeof(x) / sizeof(x[0]); ++i) {
    printf("%g, ", y[i]);
  }
  printf(")\n");
  printf("x . y = %g\n", vector_to_vector_product(x, y, 3));
}
