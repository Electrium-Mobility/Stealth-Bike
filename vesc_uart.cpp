#include "vesc_uart.h"



// void updateVescData(motorData &currentData, VescUart &vesc){
//   if (vesc.getVescValues()) {
//     currentData.speed = (uint8_t)((vesc.data.rpm) * wheel_circumference);
//     currentData.battery = (uint8_t)((vesc.data.inpVoltage) / max_voltage * 100);

//   }
// }


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