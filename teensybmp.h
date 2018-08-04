#include "i2c_t3.h" // Include library to use the other I2C pins
#ifndef teensy_bmp_h
#define teensy_bmp_h

//#if (ARDUINO >= 100)
#include "Arduino.h"
//#else
// #include "WProgram.h"
//#endif

class teensy_bmp180 {
 public:
  teensy_bmp180();
  boolean begin(uint8_t mode = 3); // 3: High resolution
  float Temperature(void);
  int32_t calculate(int32_t UT);
  uint8_t read8(uint8_t addr);
  uint16_t read16(uint8_t addr);
  void write8(uint8_t addr, uint8_t data);
  int16_t mc, md;
  uint16_t ac5, ac6;
    
  /* int16_t ac1, ac2, ac3, b1, b2, mc, md; */
  /* uint16_t ac4, ac5, ac6; */
    
};
#endif
