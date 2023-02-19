#include "TinyModbus.h"

uint16_t compute_crc(uint8_t* ADU,uint8_t n)
{
  uint8_t i;
  uint16_t u16CRC = 0xFFFF;
  for (i=0;i<n;i++){
    u16CRC = crc16_update(u16CRC, ADU[i]);
  }
  return(u16CRC);
}

uint16_t crc16_update(uint16_t crc, uint8_t a)
{
  uint8_t i;
  crc ^= a;
  for (i = 0; i < 8; ++i)
  {
    if (crc & 1) crc = (crc >> 1) ^ 0xA001;
    else crc = (crc >> 1);
  }
  return(crc);
}
