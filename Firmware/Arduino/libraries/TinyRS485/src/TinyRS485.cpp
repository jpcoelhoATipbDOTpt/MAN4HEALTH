#include "TinyRS485.h"

TinyRS485::TinyRS485(void)
{

}

void TinyRS485::begin(Stream &serial,uint8_t DE ,uint8_t RE)
{
  _serial = &serial;
  _DE = DE;
  _RE = RE;
}


void TinyRS485::transmit(uint8_t data)
{
	while (_serial->read() != -1); // flush receive buffer before transmitting request
	// Controla Enables
	// pinMode(_DE,OUTPUT);
	// pinMode(_RE,OUTPUT);
	// digitalWrite(_DE,HIGH); // Ativa DRIVER
	// digitalWrite(_RE,HIGH); // Desative RECEIVER
	
	_serial->write(data);
}

int TinyRS485::available(void)
{
	return(_serial->available());
}

uint8_t TinyRS485::receive(void)
{
		// Controla Enables

	// digitalWrite(_DE,LOW); // Ativa DRIVER
	// digitalWrite(_RE,LOW); // Desative RECEIVER
	
	return(_serial->read());
}

