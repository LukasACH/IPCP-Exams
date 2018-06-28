#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdatomic.h>

#define PI 3.1416


typedef struct Vector3 {
    double_t x;
    double_t y;
    double_t z;
} Vector3;

void rnd_init() { srand(time(NULL)); }
double_t rnd();
Vector3 rnd_sphere();
double_t generateGaussianNoise(double_t mu, double_t sigma);


int main() {
    rnd_init();
    
    for(size_t i = 0; i < 10; i++)
    {
        printf("%f\n", generateGaussianNoise(0, 0.02));
    }
    
    exit(EXIT_SUCCESS);
}



double_t rnd() {
    return (double_t)rand() / (double_t)RAND_MAX;
}

Vector3 rnd_sphere() {
    double_t t = 2 * PI * rnd();
    double_t p = fma(2, rnd(), -1);
    double_t r = cbrt(rnd());
    return (Vector3){
        r * cos(t) * sin(p),
        r * sin(t) * sin(p),
        r * cos(t) };
}

double_t generateGaussianNoise(double_t mu, double_t sigma) {
    double_t z0 = sqrt(-2.0 * log(rnd())) * cos(2 * PI * rnd());
    return fma(z0, sigma, mu);
}