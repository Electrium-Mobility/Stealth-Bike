#include "rpm.h"

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
