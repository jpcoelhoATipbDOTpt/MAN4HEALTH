#include <SoftwareSerial.h>
#include <TinyRS485.h>
#include <TinyModbus.h>
//
#define MAX485_DE 4
#define MAX485_RE 5
#define MAX485_RO 2
#define MAX485_DI 3
//

SoftwareSerial SoftSerial(MAX485_RO, MAX485_DI); // RX, TX
TinyRS485 RS485;

// ------------------------------------------------------------------------------------------------------------------
// void setup(void)
// ------------------------------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);     // Porto série (hardware) para debug
  SoftSerial.begin(115200);   // Porto série (software) usado pelo transceiver RS485

  pinMode(MAX485_DE, OUTPUT);
  pinMode(MAX485_RE, OUTPUT);

  digitalWrite(MAX485_DE, LOW); // Desativa DRIVER
  digitalWrite(MAX485_RE, LOW); // Ativa RECEIVER

  RS485.begin(SoftSerial, MAX485_DE, MAX485_RE);
}

// ------------------------------------------------------------------------------------------------------------------
// void loop(void)
// ------------------------------------------------------------------------------------------------------------------
void loop()
{
  if (RS485.available()) Serial.print(RS485.receive(), HEX);
}
