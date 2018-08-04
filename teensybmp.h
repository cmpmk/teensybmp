#include "i2c_t3.h" // Include library to use the other I2C pins
#ifndef teensy_bmp_h
#define teensy_bmp_h

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


#define bmp_addr 0x77
#define bmp_ultrahighres 3

// Define 16 bit Calibration data, read from the EEPROM 
#define AC1 0xAA
#define AC2 0xAC
#define AC3 0xAE
#define AC4 0xB0
#define AC5 0xB2
#define AC6 0xB4
#define B1  0xB6
#define B2  0xB8
#define MC  0xBC
#define MD  0xBE
#define CONTROL 0xF4
#define TEMPDATA 0xF6
#define READTEMPCMD 0x2E

class teensy_bmp180 {
 public:
  teensy_bmp180();
  boolean begin(uint8_t mode = 3); // 3: High resolution
  float Temperature(void);
  int32_t calculate(int32_t UT);
  uint8_t read8(uint8_t addr);
  uint16_t read16(uint8_t addr);
  void write8(uint8_t addr, uint8_t data);

  int16_t ac1, ac2, ac3, b1, b2, mc, md;
  uint16_t ac4, ac5, ac6;
    
};
#endif
