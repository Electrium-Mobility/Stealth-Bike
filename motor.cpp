#include "motor.h"

// vesc uart 
float inputMap(uint8_t rpm, uint8_t rpm_MAX, uint8_t rpm_START, float current_MAX, float current_MIN){
  float currentOutput;
  if (((current_MAX-current_MIN)/(rpm_MAX-rpm_START) * (rpm-rpm_START) + current_MIN) < 0){
    currentOutput = 0;
  } else{
    currentOutput = (current_MAX-current_MIN)/(rpm_MAX-rpm_START) * (rpm-rpm_START) + current_MIN; 
  }

  return currentOutput;
}

float throttleFilter(float &prev, float curr){
  if ((curr-prev) > POSITIVE_THRESHOLD){
    curr += POSITIVE_THRESHOLD;
  } else if ((prev-curr) > NEGATIVE_THRESHOLD){
    curr -= NEGATIVE_THRESHOLD;
  }

  if (curr < 0){
    curr = 0;
  } else if (curr > 17){
    curr = 17;
  }
  
  return curr;
}

// rpm
int checkForRotation(uint8_t *readingArray, uint8_t &status, uint8_t counter, uint8_t *finalReadingArray, uint8_t finalCounter){
  readingArray[counter] = digitalRead(D5);

    int sum = 0;
    for (int i{0}; i<4; i++){
      sum += readingArray[i];
    }

    if ((sum == 0 && status == 0) || (sum == 4 && status == 1)){ //If we are looking for 0s and get 0s OR if we are looking for all 1s and get 1s
      status ^= 1;
      finalReadingArray[finalCounter] = 1;
      return 1;
    } else {
      finalReadingArray[finalCounter] = 0;
      return 0;
    }
}

uint8_t rpmCalculation(uint8_t *finalReadingArray){
  uint8_t rpm = 0;
  for (int i{0}; i<200; i++){
    rpm += finalReadingArray[i];
  }
  return rpm;  
}
