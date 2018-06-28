/* Compile with: gcc -Wall 2017-3.c -O3 -o /tmp/a -lpthread -lm && time /tmp/a */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <inttypes.h>
#include "Vector3.h"
#include <pthread.h>
#include <stdatomic.h>

#define PI 3.1416

#define NUM_THREADS 4
#define TRIES_TOTAL 1000000

void rnd_init() { srand(time(NULL)); }
double_t rnd();
Vector3 rnd_sphere();
double_t generateGaussianNoise(double_t mu, double_t sigma, unsigned int *seed);
uint32_t calcParticle();
void *thread_calc(void *num);

int main() {
    rnd_init();
    
    pthread_t threads[NUM_THREADS];

    uint32_t num = (uint32_t)(TRIES_TOTAL/NUM_THREADS);
    printf("Calculating %d tries on %d threads.\nResulting in %"PRIu32" calculations per thread\n", TRIES_TOTAL, NUM_THREADS, num);

    for (size_t ptx = 0; ptx < NUM_THREADS; ++ptx) {
        pthread_create(threads+ptx, NULL, thread_calc, &num);
    }

    uint32_t sum = 0;

    for (size_t ptx = 0; ptx < NUM_THREADS; ++ptx) {
        uint32_t* sum_tmp;
        pthread_join(threads[ptx], (void**) &sum_tmp);
        sum += *sum_tmp;
        free(sum_tmp);
    }

    uint32_t n = num * NUM_THREADS;
    printf("Mean: %f\n", (double_t)sum / n);
    exit(EXIT_SUCCESS);
}

void *thread_calc(void *num) {
    unsigned int seed = rand();
    uint32_t *sum = malloc(sizeof(uint32_t));
    *sum = 0;
    for(size_t i = 0; i < *(uint32_t*)num; i++)
    {
        *sum += calcParticle(&seed);
    }
    return (void*) sum;
}

uint32_t calcParticle(unsigned int *seed) {
    Vector3 pos = rnd_sphere(seed);
    uint32_t t;
    for (t = 1; pos.x*pos.x+pos.y*pos.y+pos.z*pos.z <=1; ++t) {
        Vector3 vel = {
            generateGaussianNoise(0, 0.02, seed),
            generateGaussianNoise(0, 0.02, seed),
            generateGaussianNoise(0, 0.02, seed)
        };
        Vector3_add(&pos, vel);
    }
    return t;
}

double_t rnd(unsigned int *seed) {
    return (double_t)rand_r(seed) / (double_t)RAND_MAX;
}

double_t generateGaussianNoise(double_t mu, double_t sigma, unsigned int *seed) {
    double_t z0 = sqrt(-2.0 * log(rnd(seed))) * cos(2 * PI * rnd(seed));
    return fma(z0, sigma, mu);
}