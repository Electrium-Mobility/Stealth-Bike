#include <SoftwareSerial.h>
#include <VescUart.h>
#include <stdint.h>

#define POSITIVE_THRESHOLD 0.1
#define NEGATIVE_THRESHOLD 0.5
#define MAX_VOLTAGE 42
#define WHEEL_CIRCUMFERENCE 2.0

#define RPM_MAX 30
#define RPM_MIN 2
#define CURRENT_MAX 20
#define CURRENT_MIN 0

typedef struct{
  uint8_t speed;
  uint8_t battery;
} motorData;

//void updateVescData(motorData currentData, VescUart &vesc);
float inputMap(uint8_t rpm, uint8_t rpm_MAX, uint8_t rpm_START, float current_MAX, float current_MIN);
float throttleFilter(float &prev, float curr);