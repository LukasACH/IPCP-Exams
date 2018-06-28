#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>


uint32_t initFsr();
uint32_t step(uint32_t);
void printbinary(uint32_t);


int main() {
    uint32_t fsr = initFsr();
    uint32_t sum = 0;
    uint16_t numbers = 10000;
    for (int n = 0; n < 5; ++n){
        fsr = step(fsr);
        printbinary(fsr);
        printf(": %"PRIu32"\n", fsr);
    }

    for (int n = 0; n < numbers; ++n){
        fsr = step(fsr);
        sum += fsr;
        //printbinary(fsr);
        //printf(": %"PRIu32"\n", fsr);
    }
    printf("Sum: %"PRIu32"\n", sum);
    printf("Mean: %f\n", (double)sum / (double)numbers / (double)0xFFFFF);

    uint32_t start = fsr;
    uint32_t period = 1;
    fsr = step(fsr);
    while (fsr != start){
        fsr = step(fsr);
        period++;
    }
    printf("Period: %"PRIX32"\n", period);
    

    exit(0);
}

uint32_t initFsr() {
    srand(time(NULL));
    uint32_t fsr = 0;
    for (uint8_t idx = 0; idx < 20; ++idx) {
        fsr += exp2(idx) * (rand() % 2);
    }
    return fsr;
}

uint32_t step(uint32_t fsr) {
    uint32_t newbit = ((fsr >> 19) & 1) ^ ((fsr >> 2) & 1);
    uint32_t newfrs = ((fsr << 1) & 0xFFFFF) | newbit;
    return newfrs;
}

void printbinary(uint32_t fsr) {
    char binary[21];
    for (int idx = 0; idx < 20; ++idx) {
        binary[idx] = (fsr >> (19 - idx) & 1 ? '1' : '0');
    }
    binary[20] = '\x00';
    printf("%s", binary);
}
