// #include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "gpio.h"
#include "events.h"

void alertWaterOverflow(int gpio, int level, uint32_t tick) {
	char* pinStatus = "";
	if (level == 0) {
		pinStatus = "LOW";
	} else {
		pinStatus = "HIGH";
	}
	printf("Water OverFlow Detected! Status: %s\n", pinStatus);
}

void alertButtonPressed(int gpio, int level, uint32_t tick) {
	if (level == 1) {
		printf("Button Pressed!");
	}

	eventTrigger(EVENT_BUTTON_PRESS);
}

void initalizeGPIO() {
	if(gpioInitialise() < 0) {
		fprintf(stderr, "GPIO Initalize failure.");
		exit(1);
	}

	gpioSetMode(WATER_SENSOR_PIN, PI_INPUT);
	gpioSetPullUpDown(WATER_SENSOR_PIN, PI_PUD_UP);
	gpioSetAlertFunc(WATER_SENSOR_PIN, alertWaterOverflow);

	gpioSetMode(BUTTON_PIN, PI_INPUT);
	gpioSetPullUpDown(BUTTON_PIN, PI_PUD_UP);
	gpioSetAlertFunc(BUTTON_PIN, alertButtonPressed);
}