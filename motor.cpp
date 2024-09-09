#include "motor.h"

// vesc uart functions 

// finds the current value based on the rpm, change in rpm, and current range
float inputMap(uint8_t rpm, uint8_t rpm_MAX, uint8_t rpm_START, float current_MAX, float current_MIN){
  float currentOutput;
  // sets current to 0 if calculated value is negative
  if (((current_MAX-current_MIN)/(rpm_MAX-rpm_START) * (rpm-rpm_START) + current_MIN) < 0){
    currentOutput = 0; 
  } else {
    currentOutput = (current_MAX-current_MIN)/(rpm_MAX-rpm_START) * (rpm-rpm_START) + current_MIN; 
  }

  return currentOutput;
}

// adjusts current value if it too high or too low or if there is a significant change in current
float throttleFilter(float &prev, float curr){
  // adjuts current value if the jump from the previous value is non-negligibly large (in either direction)
  if ((curr-prev) > POSITIVE_THRESHOLD){
    curr += POSITIVE_THRESHOLD;
  } else if ((prev-curr) > NEGATIVE_THRESHOLD){
    curr -= NEGATIVE_THRESHOLD;
  }

  // adjusts current value if it is out of range (0 to 17)
  if (curr < 0){
    curr = 0;
  } else if (curr > 17){
    curr = 17;
  }
  
  return curr;
}

// rpm functions

// finds if bike wheels are rotating
int checkForRotation(uint8_t *readingArray, uint8_t &status, uint8_t counter, uint8_t *finalReadingArray, uint8_t finalCounter){
  readingArray[counter] = digitalRead(D5);

    int sum = 0;
    for (int i{0}; i<4; i++){
      sum += readingArray[i];
    }

    if ((sum == 0 && status == 0) || (sum == 4 && status == 1)){ // If we are looking for all 0s and get 0s OR if we are looking for all 1s and get 1s
      status ^= 1;
      finalReadingArray[finalCounter] = 1;
      return 1;
    } else {
      finalReadingArray[finalCounter] = 0;
      return 0;
    }
}

// finds how fast the wheels are turning: number of revolutions per minute (rpm)
uint8_t rpmCalculation(uint8_t *finalReadingArray){
  uint8_t rpm = 0;
  for (int i{0}; i<200; i++){ // counts how many times the wheels were detected rotating in the past minute
    rpm += finalReadingArray[i]; 
  }
  return rpm;
}
