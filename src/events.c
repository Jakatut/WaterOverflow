#include <pigpio.h>

#include "events.h"

void eventButtonPress() {
	printf("button pressed");
}

void initalizeEvents() {
	eventSetFunc(EVENT_BUTTON_PRESS, eventButtonPress);
}