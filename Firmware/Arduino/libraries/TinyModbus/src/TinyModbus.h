#ifndef TinyModbus_h
#define TinyModbus_h
#include "Arduino.h"

uint16_t compute_crc(uint8_t* ,uint8_t);
uint16_t crc16_update(uint16_t, uint8_t);

#endif
