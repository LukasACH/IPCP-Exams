#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint32_t run(uint32_t number);
uint64_t step(uint64_t val, uint32_t *stp);

int main() {
    uint32_t record = 0;
    uint32_t record_at = 0;
    for (uint32_t number = 1; number < 1000000; ++number) {
        uint32_t steps = run(number);
        if (record < steps) {
        //    printf("New Max found: Steps for %"PRIu32": %"PRIu32"\n", number, steps);
            record = steps;
            record_at = number;
        }
    }
    printf("Longest chain: %"PRId32" with number %"PRId32"\n", record, record_at);
    exit(EXIT_SUCCESS);
}

uint32_t run(uint32_t number) {
    uint32_t stp = 0;
    uint64_t val = number;
    while (val != 1) {
        val = step(val, &stp);
    }
    return stp;
}

uint64_t step(uint64_t val, uint32_t *stp) {
    if (val % 2 == 0) {
        *stp += 1;
        return val >> 1;
    } else {
        //if (val & 0x8000000000000000) { printf("Overflow possible"); }
        *stp += 2;
        return (val >> 1) + val + 1;
    }
}