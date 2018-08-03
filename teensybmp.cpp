/* Library for the Teensy 3.6 board to utilize the multiple I2C buses, first 
   starting with pins 3 and 4 for scl2, sda2 to interface with the Bosch BMP180 sensor */

#include "teensybmp.h"
#define WIRE2_PINS I2C_PINS_3_4

teensy_bmp180::teensy_bmp180() {}

boolean teensy_bmp180::begin(uint8_t mode) {

}
