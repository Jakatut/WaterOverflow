#include <stdlib.h>
#include "controls.h"

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
