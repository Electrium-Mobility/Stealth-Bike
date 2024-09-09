#include <stdint.h>
#include "Arduino.h"



int checkForRotation(uint8_t *readingArray, uint8_t &status, uint8_t counter, uint8_t* finalReadingArray, uint8_t finalCounter);
uint8_t rpmCalculation(uint8_t* finalReadingArray);