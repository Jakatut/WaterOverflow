#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pigpio.h>
#include <stdbool.h>

#define WATER_SENSOR_PIN 14
#define BUTTON_PIN 15
#define EVENT_BUTTON_PRESS 0

struct controls {
	double start_time;
	int duration;
	bool button_pressed;
};

typedef struct controls Controls;

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

void setDuration(Controls* controls, int argc, char *argv[]) {
	int secs = 60;
	if (argc > 1) {
		secs = atoi(argv[1]);
	}

	// Limit the duration.
	if ((secs < 1) || (secs > 3600)) {
		secs = 3600;
	}

	controls->duration = secs;
	controls->start_time = time_time();
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

void eventButtonPress() {
	printf("button pressed");
}

void initalizeEvents() {
	eventSetFunc(EVENT_BUTTON_PRESS, eventButtonPress);
}


int main(int argc, char *argv[]) {
	Controls controls;
	setDuration(&controls, argc, argv);
	initalizeGPIO();
	initalizeEvents();
	
	while(time_time() - controls.start_time < controls.duration) {
		sleep(1);
	}	

	gpioTerminate();

	return 0;

}
