#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1.0E-4L


double complex derivative(double complex (*f)(double complex), double complex z) {
  return (f(z + EPSILON) - f(z - EPSILON)) / (2 * EPSILON);
}

double complex f(double complex z) {
  return csin(z);
}

int main(int argc, char* argv[argc +1]) {
  for (size_t i = 0; i < 100; ++i) {
    double complex z = ((float)rand() / (float)(RAND_MAX)) +
      ((float)rand() / (float)(RAND_MAX)) * I;
    printf("z = %g+%gi\tf(z) = %g+%gi\tf'(z) = %g+%gi\n",
        creal(z), cimag(z),
        creal(f(z)), cimag(f(z)),
        creal(derivative(f, z)), cimag(derivative(f, z))
    );
  }

}
