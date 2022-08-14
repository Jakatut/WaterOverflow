#define WATER_SENSOR_PIN 14
#define BUTTON_PIN 15

// Registers GPIO pins and their callbacks for INPUT/OUTPUT
void initalizeGPIO();

// Alerts to register for gpio pin activity.
void alertWaterOverflow(int gpio, int level, uint32_t tick);
void alertButtonPressed(int gpio, int level, uint32_t tick);



