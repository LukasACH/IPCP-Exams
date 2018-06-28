#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1416

double_t integral(double_t(*func)(double_t), double_t xlow, double_t xup, unsigned int depth);


double_t f(double_t x) {
    //return 3.0 * tan(x) / (1.0 + pow(cos(x), 2));
    return 6.0 * tan(x) / (cos(2.0 * x) + 3.0);
}


int main(int argc, char const *argv[])
{
    double_t result = 0.0, prev_result = -1.0;
    for (unsigned int depth = 0; fabs(result - prev_result) >= 1e-6; ++depth) {
        prev_result = result;
        result = integral(&f, 0, PI / 4, depth);
        printf("Depth: %u, integral = %.7f\n", depth, result);
    }
    exit(EXIT_SUCCESS);
}


double_t integral(double_t(*func)(double_t), double_t xlow, double_t xup, unsigned int depth) {
    if (depth > 0) {
        double_t half = (xlow + xup) / 2.0;
        return integral(func, xlow, half, depth - 1) + integral(func, half, xup, depth - 1);
    }

    double_t h = (xup - xlow) / 4.0;
    double_t x1 = (3 * xlow + xup) / 4.0;
    double_t x2 = (xlow + xup) / 2.0;
    double_t x3 = (xlow + 3 * xup) / 4.0;

    double_t k0 =  7.0 * (*func)(xlow);
    double_t k1 = 32.0 * (*func)(x1);
    double_t k2 = 12.0 * (*func)(x2);
    double_t k3 = 32.0 * (*func)(x3);
    double_t k4 =  7.0 * (*func)(xup);
    return 2.0 / 45.0 * h * (k0 + k1 + k2 + k3 + k4);
}