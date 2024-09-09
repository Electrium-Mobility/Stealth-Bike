#include "oled.h"



void showBatteryLevel(uint8_t percent, uint8_t speed, U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2)
{
    uint8_t width;

    if (percent > 100)
        percent = 100;

    u8g2.clearBuffer();
    u8g2.drawHLine(52,1,11);
    u8g2.drawHLine(52,7,11);
    u8g2.drawHLine(52,2,1);
    u8g2.drawHLine(52,3,1);
    u8g2.drawHLine(52,4,1);
    u8g2.drawHLine(52,5,1);
    u8g2.drawHLine(52,6,1);

    u8g2.drawHLine(62,2,10);
    u8g2.drawHLine(62,3,10);
    u8g2.drawHLine(62,4,10);
    u8g2.drawHLine(62,5,10);
    u8g2.drawHLine(62,6,10);

    u8g2.drawBox(62,2,1,5);
    if (BATTERY_MODE_SOLID)
    {
        width = (percent * CHARGE_AREA_WIDTH) / 100;
        u8g2.drawBox(CHARGE_AREA_START_X, CHARGE_AREA_START_Y, width, CHARGE_AREA_HEIGHT);
    } else {
        uint8_t bars;
        
        
         if (percent >= 66)
        {
            // Show two bars
            bars = 3;
        }else if (percent >= 33)
        {
            // Show two bars
            bars = 2;
        } else if (percent > 0)
        {
            // Show one bar
            bars = 1;
        } else {
            // Show nothing
            bars = 0;
        }

        uint8_t offset = CHARGE_AREA_START_X;
        for (uint8_t i = 0; i < bars; i++)
        {
            u8g2.drawBox(offset, CHARGE_AREA_START_Y, 3, CHARGE_AREA_HEIGHT);
            offset += 3;
        }
    }
//speedometer code

      u8g2.drawBox(31,70,4,4);
      u8g2.drawCircle(32,74,28);
      u8g2.drawLine(4, 74, 60, 74);

    if(speed > 0 && speed <=5){
      //0 position
      u8g2.drawLine(29,72,7,72);
      u8g2.drawLine(29,71,7,71);
    }

    else if(speed > 5 && speed <= 15){
      //1st position
      u8g2.drawLine(29,72,8,66);
      u8g2.drawLine(29,71,8,65);
    }
    
    //2nd position
    else if(speed > 15 && speed <= 25){
      u8g2.drawLine(29,71,13,61);
      u8g2.drawLine(29,70,13,60);
    }
    
    //3rd position
    if(speed>25 && speed <= 35){
      u8g2.drawLine(29,69,17,55);
      u8g2.drawLine(29,68,17,54);
    }

    //4th position
    else if(speed>35 && speed < 45){
      u8g2.drawLine(30,68,25,50);
      u8g2.drawLine(31,68,25,49);
    }
    //middle position
    else if(speed >= 45 && speed <= 55){ 
      u8g2.drawLine(32,68,32,48);
      u8g2.drawLine(33,68,33,48);
    }
//mirror 4th
    if(speed > 55 && speed <= 65){
      u8g2.drawLine(34,68,39,49);
      u8g2.drawLine(33,68,39,50);
    }
//mirror 3rd
    if(speed > 65 && speed <= 75 ){
      u8g2.drawLine(36,68,47,54);
      u8g2.drawLine(36,69,47,55);
    }
//mirror 2nd
    if(speed > 75 && speed <= 85 ){
      u8g2.drawLine(36,70,52,60);
      u8g2.drawLine(36,71,51,61);
    }
//mirror 1st
    if(speed > 85 && speed < 95 ){
      u8g2.drawLine(36,70,56,65);
      u8g2.drawLine(36,71,57,66);
    }

    //last 
    if(speed >= 95 && speed <=100){
      u8g2.drawLine(36,72,58,72);
      u8g2.drawLine(36,71,58,71);
    }
  u8g2.setFont(u8g2_font_squeezed_r6_tr);
  u8g2.drawStr(24,98, "KM/H+");

    u8g2.sendBuffer();
}

void ShowBatteryPercent(uint8_t percent, U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2){
  char cstr[16];
  itoa(percent, cstr, 10);
  u8g2.setFont(u8g2_font_torussansbold8_8r);
 do {
    u8g2.setFont(u8g2_font_6x10_mr);
    if(percent == 100){
      u8g2.drawStr(28,8, cstr);
    }
    else if (percent <=99 && percent >=10){
      u8g2.drawStr(32,8, cstr);
    }

    else if (percent <= 9){
      u8g2.drawStr(38,8, cstr);
    }
    u8g2.drawStr(45,8, "%");

 }while ( u8g2.nextPage() );
  delay(1);
}

void iShowSpeed(uint8_t speed, U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2){
  char cstr[16];
  itoa(speed, cstr, 10);
  u8g2.setFont(u8g2_font_crox3c_tn);
 do {
    u8g2.setFont(u8g2_font_crox3c_tn);
    if(speed<10)
  {
    u8g2.drawStr(26,89, cstr);  
  }
  else{
    u8g2.drawStr(20,89, cstr);
      } 
 }while ( u8g2.nextPage() );
  delay(1);
}
/*
void displayKPH(){
  do {
  u8g2.setFont(u8g2_font_squeezed_r6_tr);
  u8g2.drawStr(24,98, "KM/H");
  }while ( u8g2.nextPage() );
}
*/ 



//not used right now...
/*void Speedometer(uint8_t speed){
    u8g2.clearBuffer();

    u8g2.drawBox(31,70,4,4);


    if(speed > 0 && speed <=5){
      //0 position
      u8g2.drawLine(29,72,7,72);
      u8g2.drawLine(29,71,7,71);
    }

    if(speed > 5 && speed <= 15){
      //1st position
      u8g2.drawLine(29,72,8,66);
      u8g2.drawLine(29,71,8,65);
    }
    
    //2nd position
    if(speed > 15 && speed <= 25){
      u8g2.drawLine(29,71,13,61);
      u8g2.drawLine(29,70,13,60);
    }
    
    //3rd position
    if(speed >25 && speed <= 35){
      u8g2.drawLine(29,69,17,55);
      u8g2.drawLine(29,68,17,54);
    }

    //4th position
    if(speed >35 && speed < 45){
      u8g2.drawLine(30,68,25,50);
      u8g2.drawLine(31,68,25,49);
    }
    //middle position
    if(speed >= 45 && speed < 55){ 
      u8g2.drawLine(32,68,32,45);
      u8g2.drawLine(33,68,33,45);
    }

    if(speed >= 55 && speed < 65){
      u8g2.drawLine(33,68,39,49);
      u8g2.drawLine(34,68,39,50);
    }
    
    if(speed > 65 && speed <= 75 ){
      u8g2.drawLine(35,68,47,55);
      u8g2.drawLine(35,68,47,54);
    }

    //last 
    if(speed >= 95 && speed <=100){
      u8g2.drawLine(35,72,62,72);
      u8g2.drawLine(35,71,62,71);
    }
    
        u8g2.sendBuffer();

}
*/
