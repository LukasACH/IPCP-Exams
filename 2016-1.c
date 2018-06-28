#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double_t func(double_t x);

int main() {
    double_t x0 = 2;
    double_t xn = 0;
    while (fabs(x0 - xn) > 1e-5) {
        x0 = xn;
        xn = func(x0);
    }
    printf("%f\n", xn);
}


double_t func(double_t x) {
    return cos(x) / exp(x);
}