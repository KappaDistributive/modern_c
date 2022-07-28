#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1.0E-4L

double derivative(double (*f)(double), double x) {
  return (f(x + EPSILON) - f(x - EPSILON)) / (2 * EPSILON);
}

int main(int argc, char *argv[argc + 1]) {
  for (int index = 0; index < 100; ++index) {
    double x = rand();
    printf("x = %g; sin'(x) = %g; cos(x) = %g\n", x, derivative(sin, x),
           cos(x));
  }
}
