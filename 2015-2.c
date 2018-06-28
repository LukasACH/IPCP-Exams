#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <float.h>
#include <math.h>

#define RANDU_MAX 0x7FFFFFF;
uint32_t RANDU_step(uint32_t *x) { return *x = 0x10003 * *x & 0x7FFFFFF; }
float_t fminarrf(float_t array[], size_t length);
float_t fmaxarrf(float_t array[], size_t length);

int main() {
    FILE *data = fopen("data.txt", "w");
    uint32_t seed = 1;
    float_t Narr[100000];
    double_t x, y, z;
    for (uint32_t idx = 0; idx < 100000; ++idx) {
        x = (double_t)RANDU_step(&seed) / RANDU_MAX;
        y = (double_t)RANDU_step(&seed) / RANDU_MAX;
        z = (double_t)RANDU_step(&seed) / RANDU_MAX
        Narr[idx] = 9.0 * x - 6 * y + z;
        fprintf(data, "%f %f %f\n", x, y, z);
    }
    printf("Min: %f, Max: %f\n", fminarrf(Narr, 100000), fmaxarrf(Narr, 100000));
    fclose(data);
    exit(EXIT_SUCCESS);
}

float_t fminarrf(float_t array[], size_t length) {
    float_t record = FLT_MAX;
    for (size_t idx = 0; idx < length; ++idx) {
        record = fminf(record, array[idx]);
    }
    return record;
}

float_t fmaxarrf(float_t array[], size_t length) {
    float_t record = FLT_MIN;
    for (size_t idx = 0; idx < length; ++idx) {
        record = fmaxf(record, array[idx]);
    }
    return record;
}