#include "SEN0159.h"

#define SAMPLEUPDATE 11000

// MG_PIN Sensor de CO2 ligado à porta A/D A0 

#define CO2Vcc PD7 // Fonte de alimentação para o sensor de CO2
                   // Ativa baixa.
#define LED PD6    // LED ligado ao pino 12 do ATMEGA328 (PD6)
                   // Configuração ativa-baixa                
uint16_t  PRMS=0;

unsigned long myTime;
unsigned long sampleTime;  // Mantém registo de quando é que foi feita a última aquisição do valor do CO2

// ------------------------------------------------------------------------------------------------------------------
// void setup(void)
// ------------------------------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(250000);        // Instancia porto série
  pinMode(LED, OUTPUT);
  pinMode(CO2Vcc, OUTPUT);     // Estabelece porto para controlo de CO2Vcc
  digitalWrite(CO2Vcc, LOW);   // Liga fonte de alimentação
  sampleTime = millis();       // Cria timetag inicial

}

// ------------------------------------------------------------------------------------------------------------------
// void loop(void)
// ------------------------------------------------------------------------------------------------------------------
void loop()
{
  // Liga CO2Vcc para aquecer o sensor
  digitalWrite(LED,LOW);    // Liga LED
  delay(500); // 60 segundos
  PRMS = (uint16_t) CO2ppm(MG_PIN, CO2Curve);
  Serial.println(PRMS);
  digitalWrite(LED,HIGH);   // Desliga LED
  delay(500); // 60 segundos
}
