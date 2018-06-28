#include <math.h>
#include <time.h>

double_t rnd(unsigned int *seed);

#define PI 3.1416

typedef struct Vector3 {
    double_t x;
    double_t y;
    double_t z;
} Vector3;

Vector3 rnd_sphere(unsigned int *seed) {
    double_t t = 2 * PI * rnd(seed);
    double_t p = acos(fma(2.0, rnd(seed), -1));
    double_t r = cbrt(rnd(seed));
    return (Vector3){
        r * cos(t) * sin(p),
        r * sin(t) * sin(p),
        r *          cos(p) };
}

void Vector3_add(Vector3 *a, Vector3 b) {
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}