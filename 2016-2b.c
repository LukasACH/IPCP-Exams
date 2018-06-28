#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

bool step(double_t speed, double_t *dist_remaining, double_t *time_passed);
double_t checkSpeed(double_t speed, double_t dist_total);
int main() {
	double_t dist_total = 42195.0;
	double_t speed = 17.0 / 3.6;
    
    double_t time_target = 3600.0 * 3.0;
    double_t time_used = 0.0;

    double_t speed_step = 10.0 / 3.6;

    while (true) {
        time_used = checkSpeed(speed, dist_total);
        if (time_used > time_target + 0.1){
            printf("Speed to slow: %f m/s\n", speed);
            speed += speed_step;
            speed_step /= 2.0;
        } else if (time_used < time_target - 0.1) {
            printf("Speed to fast: %f m/s\n", speed);
            speed -= speed_step;
            speed_step /= 2.0;
        } else {
            printf("Speed correct: %f m/s\n", speed);
            break;
        }
    }
	printf("Time used: %ih %im %fs\n", (int)floor(time_used / 3600.0), (int)floor(fmod(time_used / 60.0, 60.0)), fmod(time_used, 60.0));
	exit(0);
}


double_t checkSpeed(double_t speed, double_t dist_total) {
    double_t dist_current = dist_total;
	double_t time_passed = 0.0f;
    bool finnished = false;
	while (finnished == false) {
		finnished = step(speed, &dist_current, &time_passed);
		//printf("%7.2f%10.2f%10.2f\n", speed_current, dist_current, time_passed);
	}
    return time_passed;
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