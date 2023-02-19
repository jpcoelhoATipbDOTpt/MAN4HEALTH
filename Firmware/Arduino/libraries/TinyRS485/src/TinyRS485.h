#ifndef TinyRS485_h
#define TinyRS485_h
#include "Arduino.h"

class TinyRS485
{
  public:
    TinyRS485();
	
    void begin(Stream &serial,uint8_t,uint8_t);
	
	void transmit(uint8_t);
	
	virtual int available(void);
	
	uint8_t receive(void);
   
  private:
    Stream*  _serial;                                             ///< reference to serial port object
	uint8_t  _DE;
	uint8_t  _RE;
};

#endif

