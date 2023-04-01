#include <SoftwareSerial.h>
#include <TinyRS485.h>
#include <TinyModbus.h>
#include "SEN0159.h"
#include <EEPROM.h> // Utilizado no futuro para guardar novo ID do slave e parâmetros dos sensores...
#include "DFRobot_SHT20.h"
#include <Wire.h>

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
#define CO2FilterLenght       100        // Numero de amostras necessárias para filtro de média

#define LED                   PD6        // LED ligado ao pino 12 do ATMEGA328 (PD6) (ativa-baixa)   

// Termos associados à comunicação ModBus
#define MAX485_DE 4
#define MAX485_RE 5
#define MAX485_RO 2
#define MAX485_DI 3
//
#define TIMEOUT 100
#define FRAMELGTH 8
#define MYID 69
#define OFSTADDLIM 0x0003
#define BASEADDLIM 0x0008
#define LIMIT_ADDR OFSTADDLIM+BASEADDLIM

// Termos associados à medição da temperatura e humidade
#define SHT20MeasurementUpdate 60000     // Período de amostragem para a medição da temperatura e humidade (1 minuto)

// Variáveis associadas ao SHT20
//
unsigned long LastSHT20Measurement = 0; // Retem o tempo em que foi realizada a última medição do SHT20
float humidade    = 0.0;
float temperatura = 0.0;

// Variáveis associadas ao CO2
unsigned long myTimeCO2, MyTimeMB;
unsigned long LastCO2Measurement = 0; // Retem o tempo em que foi realizada a última medição do CO2
unsigned long LastHeaterTime = 0;     // Retem o tempo para aquecimento do sensor
unsigned long LastCO2Sampling = 0;    // Retem o tempo em que foi realizada a última amostragem do CO2
int CO2SampleCounter = 0;             // Contador para manter registo das amostras adquiridas.
float CO2filtrado = 0.0;                   // Retém valor relativo à soma das amostras do CO2
uint16_t CO2SUM[CO2FilterLenght];
//           CO2 (350 ppm) Temp 19.7 Humidade 58.0%
//uint16_t REGS[3] = {0x015E, 0x4CF4, 0x16AB}; // Registo associado às observações
uint16_t REGS[3] = {0x015E, 0xFC7C, 0x16AB}; // Registo associado às observações

// Variáveis associadas ao ModBus
int bufcnt = 0;
const int BUFFER_SIZE = 10;
uint8_t   RX[BUFFER_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Buffer com a mensagem recebida do master
uint8_t   TX[BUFFER_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Buffer com a mensagem de retorno para o master
int       TxLen = 0;                             // Dimensão da mensagem a enviar
uint16_t  CRC = 0x0000;                          // CRC da mensagem a enviar
uint16_t  BaseAddress = 0x0000;                  // Endereço base solicitado pelo Master
uint16_t  OfftAddress = 0x0000;                  // Offser associado ao endereço solicitado pelo Master

int i = 0; // Índice genérico usado em ciclos FOR

SoftwareSerial SoftSerial(MAX485_RO, MAX485_DI); // RX, TX
TinyRS485 RS485;
DFRobot_SHT20    sht20;
// ------------------------------------------------------------------------------------------------------------------
// MÁQUINA DE ESTADOS
// ------------------------------------------------------------------------------------------------------------------
enum estadosistema {
  SETRCVMODE, // Coloca o MAX485 no modo de receção
  WAIT4FRAME, // Agurada que uma frame completa seja recebida
  TSTINFRAME, // Verifica se há algum erro com a frame
  MESSAGE4ME, // A mensagem é para mim. Verifica se possuo a função solicitada
  RDFUNCTION,
  WEFUNCTION,
  FUNCNERROR,
  ADDREERROR,
  DECODE4RDE, // Descodifica para envio de dados
  DECODE4WTE, // Descodifica para alteração de variáveis
  ANSWERFRME, // Responde a um pedido
  ERRORFRAME, // Responde com um erro
  CO2CHKTIME, // Verifica se é altura para iniciar novo sequencia de amostragem
  CO2HEAT_ON, // Liga sensor para iniciar processo de aquecimento
  CO2HEAT_OF, // Desliga sensor
  CO2HEAT_OK, // Tempo de aquecimento completo
  CO2SAMPINI, // Inicia processo de amostragem
  CO2AUPDATE, // Atualiza registos e variáveis de estado
  CO2SPERROR, // Erro na amostragem
  SHT20CKTME, // 
  SHT20GTDTA  // STH20 get data
};

estadosistema sht20estado = SHT20CKTME;
estadosistema co2estado   = CO2CHKTIME;
estadosistema estado      = SETRCVMODE;

// ------------------------------------------------------------------------------------------------------------------
// bool checkForFrame(void)
// ------------------------------------------------------------------------------------------------------------------
bool checkForFrame()
{
  bufcnt = 0;
  if (RS485.available())
  {
    MyTimeMB = millis();
//    RX[bufcnt] = RS485.receive();
//    bufcnt++;
    // Baudrate = 115200 bps, 80 bits => 0.7 ms para receber a frame Modbus
    while ((millis() -  MyTimeMB) < TIMEOUT)
    {
      if (RS485.available())
      {
        RX[bufcnt] = RS485.receive();
        bufcnt++;
      }
    }
  }
  // O tempo terminou desde que foi recebido o primeiro caracter... verificar se a frame completa foi recebida
  if (bufcnt >= FRAMELGTH) return (true);
  else return (false);
}

// ------------------------------------------------------------------------------------------------------------------
// void setup(void)
// ------------------------------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  // ModBus
  SoftSerial.begin(115200); // Porto série (software) usado pelo transceiver RS485
  pinMode(MAX485_DE, OUTPUT);
  pinMode(MAX485_RE, OUTPUT);
  RS485.begin(Serial, MAX485_DE, MAX485_RE);
  // Sensor SHT20
  sht20.initSHT20();
  delay(100);
  sht20.checkSHT20();
  // CO2
  pinMode(LED, OUTPUT);           // LED para debug ou sinalização
  pinMode(CO2Vcc, OUTPUT);        // Estabelece porto para controlo de CO2Vcc
  digitalWrite(CO2Vcc, HIGH);     // Desliga fonte de alimentação do sensor de CO2
  digitalWrite(LED, HIGH);        // Desliga fonte de alimentação do sensor de CO2
  LastCO2Measurement   = millis() - CO2MeasurementUpdate;   // Força primeira medição
  LastSHT20Measurement = millis() - SHT20MeasurementUpdate; // Força primeira medição

}

// ------------------------------------------------------------------------------------------------------------------
// void loop(void)
// ------------------------------------------------------------------------------------------------------------------
void loop()
{

  switch (estado)
  {
    // ...................................................................................................
    // Máquina de estados ModBus
    // ...................................................................................................
    case SETRCVMODE:
      while (RS485.available()) RS485.receive(); // Limpa buffer
      SoftSerial.println("Inicio da maquina de estados");
      digitalWrite(MAX485_DE, LOW); // Desativa DRIVER
      digitalWrite(MAX485_RE, LOW); // Ativa RECEIVER
      estado = WAIT4FRAME;
      break;
    // .................................................................................................
    case WAIT4FRAME:
      if (checkForFrame()) estado = TSTINFRAME;
      else estado = sht20estado;
      break;
    // .................................................................................................
    case TSTINFRAME:
      // Mostra frame que recebeu
      for (i = 0; i < bufcnt; i++) Serial.print(RX[i], HEX);

      SoftSerial.println("");
      SoftSerial.print("MyID: ");

      SoftSerial.println(RX[0], DEC);
      // Verifica integridade...
      // RX[0]^=0x01; // Simula erro de transmissão (alteração de 1 bit)
      if (compute_crc(RX, bufcnt) == 0) { // CRC OK
        // Verifica se a frame é para mim...
        if (RX[0] == MYID) {
          SoftSerial.println("A mensagem E para mim");
          estado = MESSAGE4ME; // Sim, sou eu...
        }
        else {
          SoftSerial.println("A mensagem NAO e para mim");
          estado = WAIT4FRAME; // Nop, aguarda por nova frame...
        }
      }
      else { // ERRO DE TRANSMISSÂO
        SoftSerial.println("ERRO de CRC");
        estado = ERRORFRAME;
      }
      break;
    // .................................................................................................
    case MESSAGE4ME:
      // Verifica se o slave pode realizar a função solicitada em RX[1]
      switch (RX[1]) {
        case 0x03:  estado = RDFUNCTION;
          SoftSerial.println("Pedem para enviar qualquer coisa");
          break;
        case 0x06:  estado = WEFUNCTION;
          SoftSerial.println("Pedem para alterar qualquer coisa");
          break;
        default:    estado = FUNCNERROR;
          SoftSerial.println("Nao sei o que querem");
          break;
      }
      break;
    // .................................................................................................
    case RDFUNCTION:
      // Verifica se o endereço está dentro dos limites solicitados
      BaseAddress = (((uint16_t)RX[2]) << 8) + ((uint16_t)RX[3]); // Calcula endereço base
      OfftAddress = (((uint16_t)RX[4]) << 8) + ((uint16_t)RX[5]); // Calcula offset
      SoftSerial.print("Endereço base: ");
      SoftSerial.println(BaseAddress);
      SoftSerial.print("Offset: ");
      SoftSerial.println(OfftAddress);
      
      if (BaseAddress<BASEADDLIM || BaseAddress + OfftAddress > LIMIT_ADDR) {
        estado = ADDREERROR;
        SoftSerial.println("Endereço de leitura fora dos limites");
      }
      else {
        estado = DECODE4RDE; // Descodifica pedido de leitura
      }
      break;
    // .................................................................................................
    case WEFUNCTION:
      // Verifica se o endereço está dentro dos limites solicitados
      BaseAddress = (((uint16_t)RX[2]) << 8) + ((uint16_t)RX[3]); // Calcula endereço base
      OfftAddress = (((uint16_t)RX[4]) << 8) + ((uint16_t)RX[5]); // Calcula offset
      if (BaseAddress<BASEADDLIM || BaseAddress + OfftAddress > LIMIT_ADDR) {
        estado = ADDREERROR;
        SoftSerial.println("Endereco de escrita fora dos limites");
      }
      else {
        estado = DECODE4WTE; // Descodifica pedido de escrita
      }
      break;
    // .................................................................................................
    case FUNCNERROR:
      // Constroi frame
      SoftSerial.println("Retorna info de Function Error");
      TX[0] = MYID;
      TX[1] = RX[1] + 0x80;
      TX[2] = 0x01;
      TxLen = 3;
      estado = ANSWERFRME;
      break;
    // .................................................................................................
    case ADDREERROR:
      // Constroi frame
      SoftSerial.println("Retorna info de Address Error");
      TX[0] = MYID;
      TX[1] = RX[1] + 0x80;
      TX[2] = 0x02;
      TxLen = 3;
      estado = ANSWERFRME;
      break;
    // .................................................................................................
    case DECODE4RDE:
      SoftSerial.println("Descodifico frame e executo pedido");
      // Coleta a informação necessária para originar a resposta

      // Constroi frame
      TX[0] = MYID;
      TX[1] = RX[1];
      TX[2] = 0x02*OfftAddress;
      for (i=0;i<OfftAddress;i++){
        TX[3+2*i] = (uint8_t)(REGS[i]>>8);
        TX[3+2*i+1] = (uint8_t) REGS[i];
      }
      TxLen = 3+2*OfftAddress;
      // Rotina para execução do pedido.
      estado = ANSWERFRME;
      break;
    // .................................................................................................
    case ANSWERFRME:
      SoftSerial.println("Resposta a Frame (via RS485)");
      // Adiciona CRC à frame
      CRC   = compute_crc(TX, TxLen);
      TX[TxLen++] = (uint8_t) CRC;
      TX[TxLen++] = (uint8_t) (CRC >> 8);
      // Ativa MAX485 para TX
      digitalWrite(MAX485_DE, HIGH); // Ativa DRIVER
      digitalWrite(MAX485_RE, HIGH); // Desativa RECEIVER
      // Transmite dados...
      for (i = 0; i < TxLen; i++) RS485.transmit(TX[i]);
      estado = SETRCVMODE;
      break;
    // .................................................................................................
    case ERRORFRAME:
      SoftSerial.println("ERRO: CRC inválido");
      TX[0] = MYID;
      TX[1] = RX[1] + 0x80;
      TX[2] = 0x03;
      TxLen = 3;
      estado = ANSWERFRME;
      break;
    // ...................................................................................................
    // Máquina de estados CO2
    // ...................................................................................................
    case CO2CHKTIME:
      if ((millis() - LastCO2Measurement) >= CO2MeasurementUpdate) {
        LastCO2Measurement = millis();
        co2estado = CO2HEAT_ON;
      }
      estado = WAIT4FRAME;
      break;
    // .................................................................................................
    case CO2HEAT_ON:
      SoftSerial.println("Inicia aquecimento do sensor");
      digitalWrite(CO2Vcc, LOW);   // Liga fonte de alimentação do sensor de CO2
      digitalWrite(LED, LOW);      // Liga LED
      LastHeaterTime = millis();
      co2estado = CO2HEAT_OK;
      estado = WAIT4FRAME;
      break;
    // .................................................................................................
    case CO2HEAT_OK:
      if ((millis() - LastHeaterTime) >= CO2HeatingTime) {
        SoftSerial.println("Aquecimento finalizado... amostrando");
        //CO2SUM = 0.0;
        LastCO2Sampling = millis();
        co2estado = CO2SAMPINI;
      }
      estado = WAIT4FRAME;
      break;
    // .................................................................................................
    case CO2SAMPINI:
      if (CO2SampleCounter < CO2FilterLenght) { // Ainda não foram obtidas todas as amostras necessárias...
        if ((millis() - LastCO2Sampling) >= CO2TimeBetweenSamples) {
          CO2SUM[CO2SampleCounter] = (uint16_t) CO2ppm(MG_PIN, CO2Curve);
          CO2SampleCounter++;
          LastCO2Sampling = millis();
        }
      }
      else { // Já estão todas as amostras adquiridas...
        SoftSerial.print("Numero de amostras = ");
        SoftSerial.println(CO2SampleCounter);
        CO2SampleCounter = 0;   // Reinicia contador de amostras
        co2estado = CO2HEAT_OF; // Manda desligar o sensor
      }
      estado = WAIT4FRAME;
      break;
    // .................................................................................................
    case CO2HEAT_OF:
      SoftSerial.println("Desliga sensor");
      digitalWrite(CO2Vcc, HIGH);   // Desliga fonte de alimentação do sensor de CO2
      digitalWrite(LED, HIGH);      // Desliga LED
      co2estado = CO2AUPDATE;
      estado = WAIT4FRAME;
      break;
    // .................................................................................................
    case CO2AUPDATE:
      CO2filtrado = 0.0;
      for (int i = 0; i < CO2FilterLenght; i++) {
        CO2filtrado += float(CO2SUM[i]);
      }
      SoftSerial.print("Timetag:");                         // Debug
      SoftSerial.print(millis());
      SoftSerial.print(" CO2 = ");       
      SoftSerial.print(CO2filtrado / ((float)CO2FilterLenght));
      SoftSerial.println(" ppm");
      REGS[0] = (uint16_t) (10.0 * CO2filtrado / ((float)CO2FilterLenght));
      co2estado = CO2CHKTIME;
      estado = WAIT4FRAME;
      break;
    // .................................................................................................
    case CO2SPERROR:
      break;
    // ...................................................................................................
    // Máquina de estados SHT20
    // ...................................................................................................
    case SHT20CKTME:
      if ((millis() - LastSHT20Measurement) >= SHT20MeasurementUpdate) {
        LastSHT20Measurement = millis();
        sht20estado = SHT20GTDTA;
      }
      estado = co2estado;
      break;
    // .................................................................................................
    case SHT20GTDTA:
      humidade = sht20.readHumidity();                  // Observa humidade do ar
      temperatura = sht20.readTemperature();            // Observa temperaura do ar
      REGS[1] = (uint16_t) (100*temperatura);
      REGS[2] = (uint16_t) (100*humidade);
      SoftSerial.print("Timetag:");                         // Debug
      SoftSerial.print(millis());
      SoftSerial.print(" T = ");                            
      SoftSerial.print(temperatura, 1);
      SoftSerial.print("ºC");
      SoftSerial.print(" RH = ");
      SoftSerial.print(humidade, 1);
      SoftSerial.println("%");
      sht20estado = SHT20CKTME;
      estado = co2estado;
      break;
  }
}
