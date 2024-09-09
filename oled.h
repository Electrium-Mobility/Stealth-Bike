#include <Wire.h>
#include <U8g2lib.h>
#include <stdint.h>

#define FONT_USED      u8x8_font_pxplusibmcgathin_f

void showBatteryLevel(uint8_t percent, uint8_t speed, U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2);
void ShowBatteryPercent(uint8_t percent, U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2);
void iShowSpeed(uint8_t speed, U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2);




// This is the area inside the battery bitmap, in pixels
#define CHARGE_AREA_START_X     53
#define CHARGE_AREA_START_Y     2
#define CHARGE_AREA_WIDTH       3
#define CHARGE_AREA_HEIGHT      5

// This is the battery fill mode
// BATTERY_MODE_SOLID = 1 means the battery bitmap will be filled with
// a solid rectangle according to the battery charge.
// BATTERY_MODE_SOLID = 0 means the battery will be filled with a
// rectangle subdivided in 3. If the battery level is 66% or more, it will
// draw 3 rectangles. If it's 33% or more, it will draw 2 rectangles. It will
// draw 1 rectagle if the battery is less than 33%.

#define BATTERY_MODE_SOLID 0

// This is the main function, and the one you will want to transplant to your
// code. Pass the battery charge percent and it will draw the battery with
// the corresponding charge level.
// void showBatteryLevel(uint8_t percent, uint8_t speed);
// void ShowBatteryPercent(uint8_t percent);
// void iShowSpeed(uint8_t speed);
// void OLEDDisplay(void);




