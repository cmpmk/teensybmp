/* Library for the Teensy 3.6 board to utilize the multiple I2C buses, first 
   with pins 3. 4 as scl2, sda2 to interface with the Bosch BMP180 sensor */

#include "teensybmp.h"
#define WIRE2_PINS I2C_PINS_3_4

teensy_bmp180::teensy_bmp180() {}

boolean teensy_bmp180::begin(uint8_t mode) {
  mode = 3; // Ultra High Resolution mode
  Wire2.begin(I2C_MASTER, 0x00, WIRE2_PINS, I2C_PULLUP_EXT, 400000);
  
  if (read8(0xD0) != 0x55) return false;
  // Define 16 bit Calibration data, read from the EEPROM 
  //ac1 = read16(AC1);
  //ac2 = read16(AC2);
  //ac3 = read16(AC3);
  //ac4 = read16(AC4);
  ac5 = read16(0xB2);
  ac6 = read16(0xB4);

  //b1 = read16(B1);
  //b2 = read16(B2);
  mc = read16(0xBC);
  md = read16(0xBE);
  return true;
}

// Compute data read from sensor, variables used from datasheet:
int32_t teensy_bmp180::calculate(int32_t UT) {
  int32_t x1 = (UT - (int32_t)ac6) * ((int32_t)ac5) >> 15;
  int32_t x2 = ((int32_t)mc << 11) / (x1 + (int32_t)md);
  return x1 + x2;
}

// Read temperature function by converting the raw temperature data:
float teensy_bmp180::Temperature(void) {
  int32_t B5; float temperature;

  // Read raw temperature data: (control, readtempcmd)
  write8(0xF4, 0x2E);
  delay(5); // Wait 4.5ms according to datasheet
  int32_t UT = read16(0xF6); // Temperature data

  B5 = calculate(UT);
  temperature = (B5 + 8) >> 4;
  temperature /= 10;

  return temperature;
}

uint8_t teensy_bmp180::read8(uint8_t a) {
  uint8_t ret;

  Wire2.beginTransmission(0x77);
#if (ARDUINO >= 100)
  Wire2.write(a);
#else
  Wire2.send(a);
#endif
  Wire2.endTransmission();

  Wire2.beginTransmission(0x77);
  Wire2.requestFrom(0x77, 1);
#if (ARDUINO >= 100)
  ret = Wire2.read();
#else
  ret = Wire2.receive();
#endif
  Wire2.endTransmission();
  return ret;
}

uint16_t teensy_bmp180::read16(uint8_t a) {
  uint16_t ret;

  Wire2.beginTransmission(0x77);
#if (ARDUINO >= 100)
  Wire2.write(a);
#else
  Wire2.send(a);
#endif
  Wire2.endTransmission();

  Wire2.beginTransmission(0x77);
  Wire2.requestFrom(0x77, 2);

#if (ARDUINO >= 100)
  ret = Wire2.read();
  ret <<= 8; ret |= Wire2.read();
#else
  ret = Wire2.receive();
  ret <<= 8; ret |= Wire2.receive();
#endif
  Wire2.endTransmission();

  return ret;
}
  
void teensy_bmp180::write8(uint8_t a, uint8_t d) {
  Wire2.beginTransmission(0x77);
#if (ARDUINO >= 100)
  Wire2.write(a);
  Wire2.write(d);
#else
  Wire2.send(a); // Send register address to read from
  Wire2.send(d); // Write data
#endif
  Wire2.endTransmission();
}
