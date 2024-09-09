#include <SoftwareSerial.h>
#include <VescUart.h>
#include <stdint.h>
#include "Arduino.h"

// vesc uart
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

// vesc uart
float inputMap(uint8_t rpm, uint8_t rpm_MAX, uint8_t rpm_START, float current_MAX, float current_MIN);
float throttleFilter(float &prev, float curr);

// rpm
int checkForRotation(uint8_t *readingArray, uint8_t &status, uint8_t counter, uint8_t* finalReadingArray, uint8_t finalCounter);
uint8_t rpmCalculation(uint8_t* finalReadingArray);