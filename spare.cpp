// #include "oled.h"
// #include "vesc_uart.h"
// #include "rpm.h"

// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R1,/* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA); //Configure display and set I2C display pins

// VescUart vesc; //Create VescUart object for interacting with motor controller

// SoftwareSerial vescSerial(D7, D8); //Create a software interface for UART (may be able to transition to hardware UART communication on ESP8266) 

// uint8_t finalReadingArray[200];

// motorData currentData = {100,100};
// uint8_t inputArray[4] = {1,1,1,1};
// uint8_t counter = 0;
// uint8_t status = 0;
// uint8_t finalCounter = 0;
// float currentOutput = 1;
// float prevOutput = 1;

// void setup() {
//   Serial.begin(9600);
//   u8g2.begin(); //OLED initialization
//   vescSerial.begin(9600); //Vesc UART initialization
//   vesc.setSerialPort(&vescSerial);

//   for (int i = 0; i<200; i++){
//     finalReadingArray[i] = 0;
//   }
//   pinMode(D3, INPUT_PULLUP);

//   finalCounter = 0;
//   currentOutput = 1;
//   prevOutput = 1;

//   currentData = {100,100};
// }


// #define RPM_MAX 50
// #define RPM_MIN 1
// #define CURRENT_MAX 30
// #define CURRENT_MIN 0

// void loop() {
//   updateVescData(currentData, vesc);
  

//   for (int i{0}; i<200; i++){
//     prevOutput = currentOutput;

//   checkForRotation(inputArray, status, counter, finalReadingArray, finalCounter);
//   currentOutput = rpmCalculation(finalReadingArray);
//   currentOutput = inputMap(currentOutput, RPM_MAX, RPM_MIN , CURRENT_MAX, CURRENT_MIN);
//   currentOutput = throttleFilter(prevOutput, currentOutput);
//   vesc.setCurrent(currentOutput);
//   //Serial.println(currentOutput);
//   //Get VESC data to display on OLED
//    counter = (counter == 4) ? 0 : counter+1;
//    finalCounter = (finalCounter == 200) ? 0 : finalCounter+1;
//   }
//   delay(1);

//   //Serial.println(currentData.speed);
//   showBatteryLevel(currentData.battery, currentData.speed, u8g2);
//   ShowBatteryPercent(currentData.battery, u8g2);
//   iShowSpeed(currentData.speed, u8g2);

// }


// void updateVescData(motorData &currentData, VescUart vesc){
//   if (vesc.getVescValues()) {
//     currentData.speed = (uint8_t)((vesc.data.rpm) * wheel_circumference);
//     Serial.println(vesc.data.rpm);
//     currentData.battery = (uint8_t)((vesc.data.inpVoltage) / max_voltage * 100);

//   }
// }


