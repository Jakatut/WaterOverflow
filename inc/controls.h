#include <stdbool.h>

struct controls {
	double start_time;
	int duration;
	bool button_pressed;
};

typedef struct controls Controls;

void setDuration(Controls* controls, int argc, char *argv[]);