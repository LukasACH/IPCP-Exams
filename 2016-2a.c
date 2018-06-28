#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

bool step(double_t speed, double_t *dist_remaining, double_t *time_passed);

int main() {
	double_t dist_total = 42195.0;
	double_t speed = 17.0 / 3.6;
	bool finnished = false;;

	double_t dist_current = dist_total;
	double_t speed_current = speed;
	double_t time_passed = 0.0f;
	while (finnished == false) {
		finnished = step(speed, &dist_current, &time_passed);
		printf("%7.2f%10.2f%10.2f\n", speed_current, dist_current, time_passed);
	}
	printf("Time used: %ih %im %fs\n", (int)floor(time_passed / 3600.0), (int)floor(fmod(time_passed / 60.0, 60.0)), fmod(time_passed, 60.0));
	exit(0);
}

bool step(double_t speed, double_t *dist_remaining, double_t *time_passed) {
	double_t speed_current = speed * pow(0.99, floor(fmax(*time_passed - 3000.0, 0) / 600.0));
	printf(">%f\n", floor(fmax(*time_passed - 3000.0, 0) / 600.0));
	double_t dist_remaining_10m = fma(speed_current, -600.0, (*dist_remaining));
	//printf("%f\n", dist_remaining_10m);
	if (dist_remaining_10m > 0) {
		*time_passed += 600.0;
		*dist_remaining = dist_remaining_10m;
		return false;
	} else {
		*time_passed += *dist_remaining / speed_current;
		*dist_remaining = 0;
		return true;
	}
}