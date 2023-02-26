#include <SoftwareSerial.h>
#include <TinyRS485.h>
#include <TinyModbus.h>
#include "SEN0159.h"
#include <EEPROM.h> // Utilizado no futuro para guardar novo ID do slave e parâmetros dos sensores...


// Termos associados à medição do CO2
// MG_PIN - Sensor de CO2 ligado à porta A/D A0
//#define CO2Vcc                PD7        // Fonte de alimentação para o sensor de CO2 (Ativa baixa).
//#define CO2MeasurementUpdate  1*3600000  // Período de amostragem para a medição do CO2 (em horas convertidas para millisegundos)
//#define CO2HeatingTime        5*60000    // Tempo necessário para pré-aquecer o sensor
//#define CO2TimeBetweenSamples 1*1000     // Tempo utilizado entre amostras consecutivas do CO2 (filtragem)
//#define CO2FilterLenght       1*60       // Numero de amostras necessárias para filtro de média
//#define LED                   PD6        // LED ligado ao pino 12 do ATMEGA328 (PD6) (ativa-baixa)   

// Para testes    |------|---|---|------|------|------|
// tempo (min)    0      1  1.5  2      3      4      5
// Duty cycle 1.5/5 = 30%

#define CO2Vcc                PD7        // Fonte de alimentação para o sensor de CO2 (Ativa baixa).
#define CO2MeasurementUpdate  300000     // Período de amostragem para a medição do CO2 (5 minutos)
#define CO2HeatingTime        60000      // Tempo necessário para pré-aquecer o sensor  (1 minuto)
#define CO2TimeBetweenSamples 500        // Tempo utilizado entre amostras consecutivas (1/2 segundo)
#define CO2FilterLenght       1*60       // Numero de amostras necessárias para filtro de média
#define LED                   PD6        // LED ligado ao pino 12 do ATMEGA328 (PD6) (ativa-baixa)   


//
uint16_t REGS[3] = {0, 0, 0}; // Registo associado às observações
//
unsigned long myTime;
unsigned long LastCO2Measurement = 0; // Retem o tempo em que foi realizada a última medição do CO2
unsigned long LastHeaterTime = 0;     // Retem o tempo para aquecimento do sensor
unsigned long LastCO2Sampling = 0;    // Retem o tempo em que foi realizada a última amostragem do CO2
int CO2SampleCounter = 0;             // Contador para manter registo das amostras adquiridas.
float CO2filtrado = 0.0;                   // Retém valor relativo à soma das amostras do CO2
uint16_t CO2SUM[CO2FilterLenght];
int i = 0; // Índice genérico usado em ciclos FOR


// ------------------------------------------------------------------------------------------------------------------
// MÁQUINA DE ESTADOS PRINCIPAL
// ------------------------------------------------------------------------------------------------------------------
enum co2sensorstate {
  CO2CHKTIME, // Verifica se é altura para iniciar novo sequencia de amostragem
  CO2HEAT_ON, // Liga sensor para iniciar processo de aquecimento
  CO2HEAT_OF, // Desliga sensor
  CO2HEAT_OK, // Tempo de aquecimento completo
  CO2SAMPLER, // Adquire nova amostra
  CO2SAMPINI, // Inicia processo de amostragem
  CO2AUPDATE, // Atualiza registos e variáveis de estado
  CO2SPERROR  // Erro na amostragem
} co2estado = CO2HEAT_ON;


// ------------------------------------------------------------------------------------------------------------------
// void setup(void)
// ------------------------------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);        // LED para debug ou sinalização
  pinMode(CO2Vcc, OUTPUT);     // Estabelece porto para controlo de CO2Vcc
  digitalWrite(CO2Vcc, HIGH);  // Desliga fonte de alimentação do sensor de CO2
  digitalWrite(LED, HIGH);  // Desliga fonte de alimentação do sensor de CO2
  LastCO2Sampling = millis();  // Atualiza timetag
}

// ------------------------------------------------------------------------------------------------------------------
// void loop(void)
// ------------------------------------------------------------------------------------------------------------------
void loop()
{
  // ...................................................................................................
  // Máquina de estados
  // ...................................................................................................
  switch (co2estado)
  {
    // .................................................................................................
    case CO2CHKTIME:
      if ((millis() - LastCO2Measurement) >= CO2MeasurementUpdate) {
        LastCO2Measurement = millis();
        co2estado = CO2HEAT_ON;
      }
      break;
    // .................................................................................................
    case CO2HEAT_ON:
      Serial.println("Inicia aquecimento do sensor");
      digitalWrite(CO2Vcc, LOW);   // Liga fonte de alimentação do sensor de CO2
      digitalWrite(LED, LOW);      // Liga LED
      LastHeaterTime = millis();
      co2estado = CO2HEAT_OK;
      break;
    // .................................................................................................
    case CO2HEAT_OK:
      if ((millis() - LastHeaterTime) >= CO2HeatingTime) {
        Serial.println("Aquecimento finalizado... amostrando");
        //CO2SUM = 0.0;
        LastCO2Sampling = millis();
        co2estado = CO2SAMPINI;
      }
      break;
    // .................................................................................................
    case CO2SAMPINI:
      if (CO2SampleCounter < CO2FilterLenght) { // Ainda não foram obtidas todas as amostras necessárias...
        if ((millis() - LastCO2Sampling) >= CO2TimeBetweenSamples) {
          CO2SUM[CO2SampleCounter]= (uint16_t) CO2ppm(MG_PIN, CO2Curve);
          CO2SampleCounter++;
          LastCO2Sampling = millis();
        }
      }
      else { // Já estão todas as amostras adquiridas...
        Serial.print("Numero de amostras = ");
        Serial.println(CO2SampleCounter);
        CO2SampleCounter = 0;   // Reinicia contador de amostras
        co2estado = CO2HEAT_OF; // Manda desligar o sensor
      }
      break;
    // .................................................................................................
    case CO2HEAT_OF:
      Serial.println("Desliga sensor");
      digitalWrite(CO2Vcc, HIGH);   // Desliga fonte de alimentação do sensor de CO2
      digitalWrite(LED, HIGH);      // Desliga LED
      co2estado = CO2AUPDATE;
      break;
    // .................................................................................................
    case CO2AUPDATE:
      //REGS[0] = (uint16_t)(CO2SUM / (float)CO2FilterLenght); // Coloca valor no registo
      //Serial.print("CO2 (ppm) = ");
      //Serial.println(REGS[0]);
       CO2filtrado=0.0;
      for (int i=0;i<CO2FilterLenght;i++){
        Serial.println(CO2SUM[i]);
        CO2filtrado+=float(CO2SUM[i]);
      }
      Serial.print ("Valor Filtrado = ");
      Serial.println(CO2filtrado/((float)CO2FilterLenght));
      co2estado = CO2CHKTIME;
      break;
    // .................................................................................................
    case CO2SPERROR:

      break;
  }
}
