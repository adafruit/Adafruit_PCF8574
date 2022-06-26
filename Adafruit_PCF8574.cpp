/*!
 *  @file Adafruit_PCF8574.cpp
 *
 *  @mainpage Adafruit PCF8574 I2C Potentiometer
 *
 *  @section intro_sec Introduction
 *
 * 	I2C Driver for the NXP PCF8574 I2C GPIO expander
 *
 * 	This is a library for the Adafruit PCF8574 breakout:
 * 	http://www.adafruit.com/products
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *  @section dependencies Dependencies
 *
 *  This library depends on the Adafruit BusIO library
 *
 *  @section author Author
 *
 *  ladyada for Adafruit Industries
 *
 * 	@section license License
 *
 * 	BSD (see license.txt)
 *
 * 	@section  HISTORY
 *
 *     v1.0 - First release
 */

#include "Adafruit_PCF8574.h"

/*!
 *    @brief  Instantiates a new PCF8574 class
 */
Adafruit_PCF8574::Adafruit_PCF8574(void) {}

/*!
 *    @brief  Sets up the hardware and initializes I2C
 *    @param  i2c_address
 *            The I2C address to be used.
 *    @param  wire
 *            The Wire object to be used for I2C connections.
 *    @return True if initialization was successful, otherwise false.
 */
bool Adafruit_PCF8574::begin(uint8_t i2c_address, TwoWire *wire) {
  delete(i2c_dev);

  i2c_dev = new Adafruit_I2CDevice(i2c_address, wire);

  if (!i2c_dev->begin()) {
    return false;
  }

  return true;
}


bool Adafruit_PCF8574::digitalWriteByte(uint8_t d) {
  _writebuf = d;
  return i2c_dev->write(&_writebuf, 1);
}

uint8_t Adafruit_PCF8574::digitalReadByte(void) {
  i2c_dev->read(&_readbuf, 1);
  return _readbuf;
}

bool Adafruit_PCF8574::digitalWrite(uint8_t pinnum, bool val) {
  if (val) {
    _writebuf |= 1 << pinnum;
  } else {
    _writebuf &= ~(1 << pinnum);
  }
  return i2c_dev->write(&_writebuf, 1);
}


bool Adafruit_PCF8574::pinMode(uint8_t pinnum, uint8_t val) {
  if ((val == INPUT) || (val == INPUT_PULLUP)) {
    _writebuf |= 1 << pinnum;
  } else {
    _writebuf &= ~(1 << pinnum);
  }
  return i2c_dev->write(&_writebuf, 1);
}


bool Adafruit_PCF8574::digitalRead(uint8_t pinnum) {
  i2c_dev->read(&_readbuf, 1);
  return (_readbuf >> pinnum) & 0x1;
}
