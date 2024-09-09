#include "oled.h"
#include "motor.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R1, /* reset=*/U8X8_PIN_NONE, /* clock=*/SCL, /* data=*/SDA);
/** Initiate SoftwareSerial class */

// libraries
#include <VescUart.h>
#include <SoftwareSerial.h>

/** Initiate VescUart class */
VescUart vesc;

/** Initiate SoftwareSerial class */
SoftwareSerial vescSerial(13, 15);

uint8_t finalReadingArray[200]; // keeps track of how often wheels are rotating
uint8_t inputArray[4] = { 1, 1, 1, 1 }; // finds if wheels are rotating or not
uint8_t counter = 0; // loops through all 4 input array values
uint8_t status = 0; // if wheels are rotating or not (rotating == 1, not rotating == 0)
uint8_t finalCounter = 0; // loops through all 200 final reading array values
float currentOutput = 0; // current value
float prevOutput = 0; // previous current value
uint8_t percent = 100; // battery percentage
uint8_t speed = 100; // speed of bike


void setup() {
  u8g2.begin();

  /** Setup Serial port to display data */
  Serial.begin(9600);

  /** Setup SoftwareSerial port */
  vescSerial.begin(9600);

  /** Define which ports to use as UART */
  vesc.setSerialPort(&vescSerial);
  for (int i = 0; i < 200; i++) {
    finalReadingArray[i] = 0;
  }
  pinMode(D5, INPUT_PULLUP);
}


void loop() {
  prevOutput = currentOutput;
  /** Call the function getVescValues() to acquire data from VESC */
  if ( vesc.getVescValues() ) {
    speed = (uint8_t)((vesc.data.rpm) * WHEEL_CIRCUMFERENCE * 60/23000); // calculate speed based on rpm
    percent = (uint8_t)(((vesc.data.inpVoltage) - 36 )/ (MAX_VOLTAGE - 36) * 100); // calculate battery percent based on voltage
  }

    // displays values on oled display
    showBatteryLevel(percent, speed, u8g2);
    ShowBatteryPercent(percent, u8g2);
    iShowSpeed(speed, u8g2);

  for (int i{0}; i < 200; i++) {
  checkForRotation(inputArray, status, counter, finalReadingArray, finalCounter); // checks if bike is rotating
  currentOutput = rpmCalculation(finalReadingArray); // finds how fast the wheels are turning (rpm)
  currentOutput = inputMap(currentOutput, RPM_MAX, RPM_MIN , CURRENT_MAX, CURRENT_MIN); // finds current
  currentOutput = throttleFilter(prevOutput, currentOutput); // adjusts current value, ensuring it is within range
  Serial.println(currentOutput);
  vesc.setCurrent(currentOutput); // sets the motor current

  counter = (counter == 4) ? 0 : counter+1; // checks input value 4 times, to reduce noise and ensure wheels are rotating or not
  finalCounter = (finalCounter == 200) ? 0 : finalCounter+1; // sets all values in reading array, to keep track of previous rotation values to find rpm
  }


  delay(1);
}