#define EVENT_BUTTON_PRESS 0

// Registers events via pigpio.
void initalizeEvents();

// callbacks for event registry.
void eventButtonPress();