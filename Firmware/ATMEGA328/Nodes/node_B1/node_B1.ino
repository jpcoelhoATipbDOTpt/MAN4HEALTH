/********************************************************************************************************************
 * Nó A2
 ********************************************************************************************************************
   Variables del código

   cd = var_0 = batería
   zz = var_1 = temperatura del suelo 10cm
   zx = var_2 = temperatura del suelo 20cm
   zc = var_3 = temperatura del suelo 30cm
   zv = var_4 = humedad del suelo
   zb = var_5 = lux (se disponível)
   al = var_6 = temperatura del aire (DHT22)
   ax = var_7 = humedad del aire (DHT22)

*/

#include <SPI.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include "LoRaWAN.h"
#include "dht.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <VEML7700.h>

// ------------------------------------------------------------------------------------------------------------------
// ALIASES
// ------------------------------------------------------------------------------------------------------------------
#define LED  6         // LED que pode ser utilizado para DEBUG (ativo baixo)
#define OE   5         // Ativa/desativa logic level converter
#define EN   4         // Ativa/desativa buck-boost para +3V3
#define ordemFiltro 25 // Ordem do filtro de média

#define Vbat A0        // Pino usado na medição da tensão da bateria (a partir de divisor resistivo Vbat/2
#define THar 2         // Pino usado na medição da temperatura e humidade do ar com DHT22

// ------------------------------------------------------------------------------------------------------------------
// VARIÁVEIS GLOBAIS
// ------------------------------------------------------------------------------------------------------------------
volatile int sleep_count = 0; // Mantém registo do número de vezes que o MCU acordou desde a última transmissão
const int sleep_total = 450;    // Define o período entre transmissões calculada como sleep_total x 8s.
// Para 1 hora => sleep_total = 450. Poderá ser necessário alterar o valor do prescale
// do WDT para outros intervalos de tempo. Por exemplo, se o ciclo de trabalho for 1
// minuto, na atual condição, sleep_total = 7.5 o que não é possível dado que sleep_
// _total deve ser inteiro. No entanto, ajustando o WDT para 1 segundo, sleep_total=60
char var_0[8] = {"\0"};       // Leitura da A/D 0 (Tensão da bateria)
char var_1[8] = {"\0"};       // Leitura da A/D 1 (Genérico)
char var_2[8] = {"\0"};       // Leitura da A/D 2 (Genérico)
char var_3[8] = {"\0"};       // Leitura da A/D 3 (Genérico)
char var_4[8] = {"\0"};       // Leitura da A/D 4 (Genérico)
char var_5[8] = {"\0"};       // Leitura da A/D 5 (Genérico)
char var_6[8] = {"\0"};       // Leitura da temperatura (DTH@PD2)
char var_7[8] = {"\0"};       // Leitura da humidade relativa (DTH@PD2)

char data2send[150];

float lux;

float temp10 = -999.9, temp20 = -999.9, temp30 = -999.9; // Variáveis que retêm os valores retornados pelo sensores de
// temperatura do solo. No caso de erro de medida por falha do
// sensor, o valor dos dados é definido como -999.9

// ------------------------------------------------------------------------------------------------------------------
// OBJETOS
// ------------------------------------------------------------------------------------------------------------------
dht DHT;
OneWire ourWire(16);                //Se establece el pin A2 como bus OneWire

DallasTemperature sensorTemperatura1Wire(&ourWire); //Se declara una variable u objeto para nuestro sensor

DeviceAddress address10 = {0x28, 0xB2, 0x6F, 0x57, 0x04, 0x12, 0x3C, 0xA9};
DeviceAddress address20 = {0x28, 0xB5, 0x8A, 0x57, 0x04, 0x8E, 0x3C, 0xAA};
DeviceAddress address30 = {0x28, 0xF8, 0xE4, 0x81, 0xE3, 0x74, 0x3C, 0xED};

VEML7700 als;
// ------------------------------------------------------------------------------------------------------------------
// VETORES DE INTERRUPÇÃO
// ------------------------------------------------------------------------------------------------------------------
ISR(WDT_vect) {
  sleep_count++; // Incrementa sleep counter
}
// ------------------------------------------------------------------------------------------------------------------
// WATCHDOG
// ------------------------------------------------------------------------------------------------------------------
void watchdogOn() {
  cli();
  wdt_reset();
  // Começa por fazer o reset ao watchdog
  //MCUSR &= ~(1 << WDRF);
  // Estabelece interrupções do watchdog
  // WDCE: Watchdog Change Enable -  necessário para alterar os valores do
  //                                 watchdog (colocado automaticamente a
  //                                 zero ao fim de 4xclk
  // WDE: Watchdog System Reset Enable - Na realidade, este bit é controlado
  //                                     por WDRF. Se WDRF = 1 então WDE = 1
  WDTCSR = (1 << WDCE) | (1 << WDE);
  // Inicia watchdog timer com prescaler (8 segundos) WDP3:WDP0 = "1001"
  // WDIW: Watchdog Interrupt Enable - Se WDE = 0 o watchdog está em modo
  //                                   interrupção e se WDE=1 está em modo
  //                                   interrução + reset
  // WDTCSR = (1<<WDIE)|(1<<WDP3)|(1<<WDP0); //(8 segundos)
  WDTCSR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0);
  sei();
}

void watchdogOff() {
  cli();
  wdt_reset();
  // Começa por fazer o reset ao watchdog
  MCUSR &= ~(1 << WDRF);
  // Estabelece interrupções do watchdog
  // WDCE: Watchdog Change Enable -  necessário para alterar os valores do
  //                                 watchdog (colocado automaticamente a
  //                                 zero ao fim de 4xclk
  // WDE: Watchdog System Reset Enable - Na realidade, este bit é controlado
  //                                     por WDRF. Se WDRF = 1 então WDE = 1
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  // Inicia watchdog timer com prescaler (8 segundos) WDP3:WDP0 = "1001"
  // WDIW: Watchdog Interrupt Enable - Se WDE = 0 o watchdog está em modo
  //                                   interrupção e se WDE=1 está em modo
  //                                   interrução + reset
  // WDTCSR = (1<<WDIE)|(1<<WDP3)|(1<<WDP0); //(8 segundos)
  WDTCSR = 0x00;
  sei();
}
// ------------------------------------------------------------------------------------------------------------------
// SLEEP CONFIG
// ------------------------------------------------------------------------------------------------------------------
void goToSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Estabelece tipo de suspensão
  cli ();                              // Desabilita interrupções
  sleep_enable();                      // Habilita modo de suspensão
  sleep_bod_disable();                 // Desativa BOD
  sei ();                              // Habilita interrupções
  sleep_cpu();                         // Suspende MCU.
  sleep_disable();                     // o WDT acordou o MCU: resume a partir daqui
}
// ------------------------------------------------------------------------------------------------------------------
// INICIALIZA MCU
// ------------------------------------------------------------------------------------------------------------------
void setup() {

  Serial.begin(115200);
  
  sensorTemperatura1Wire.begin();   //Se inicia el sensor
      
  Serial.println("ola");

  SPI.setDataMode(SPI_MODE0); // Inicializa comunicação SPI com RFM95
  SPI.begin();                //
  pinMode(NSS, OUTPUT);       // Configura pinos de I/O para comunicação com RFM95
  pinMode(DIO0, INPUT);       //
  pinMode(OE, OUTPUT);        // Configura pinos para habilitar conversores DC/DC
  pinMode(EN, OUTPUT);        //

  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  digitalWrite(NSS, LOW);     // Ativa NSS
  digitalWrite(OE, LOW);      // Liga Buck-boost
  digitalWrite(EN, LOW);      // Liga Logic Level Controller
  delay(100);                 // Aguarda por estabilização da tensão
  analogReference(EXTERNAL);  // Estabelece tensão de referência da ADC como externo
    Serial.println("Fim do Setup");

  watchdogOn();               // Configura e ativa watchdog

}
// ------------------------------------------------------------------------------------------------------------------
// leitura com filtro passa-baixo
// ------------------------------------------------------------------------------------------------------------------
float leituraAnalogica(const byte port)
{
  ADCSRA |= _BV(ADEN);   // Ativa ADC
  float valorFiltrado = 0;
  for (int i = 0; i < ordemFiltro; i++) {
    valorFiltrado += (float)analogRead(port);
    delayMicroseconds(50);
  }
  ADCSRA &= ~_BV(ADEN); // Desativa ADC
  // Filtro de média...
  return (valorFiltrado / (float)ordemFiltro);
}

// ------------------------------------------------------------------------------------------------------------------
// CALCULA O NUMERO DE CARATERES NA MENSAGEM A ENVIAR
// ------------------------------------------------------------------------------------------------------------------
int bytes2send(char *data)
{
  int i = 0;
  while (data[i] != '\0') i++;
  return i;
}

// ------------------------------------------------------------------------------------------------------------------
// AQUISIÇÃO e TRANSMISSÃO
// ------------------------------------------------------------------------------------------------------------------
void loop() {
  

  goToSleep(); // Entra em suspensão
  if (sleep_count >= sleep_total) {  // Depois de acordado verifica se já é hora de transmitir

    watchdogOff();


  
    Serial.println("acordou");


    char data[200] = "\0";

    digitalWrite(NSS, HIGH);    // Ativa NSS
    digitalWrite(OE, HIGH);     // Liga Buck-boost
    digitalWrite(EN, HIGH);     // Liga Logic Level Controller
    delay(5000);                // Aguarda por estabilização da tensão (necessário para o DHT11)
        Wire.begin();  // para resolver el problema de los 1.7V en el modo sleep

  als.begin();
  als.setGain(VEML7700::ALS_GAIN_d8); //necesario para correcta medición de valores altos de lux
  
    RFM_Init();                 // Inicializa RFM95
    // ...Mede valor da tensão da bateria...........................................................................
    dtostrf(leituraAnalogica(Vbat), 0, 1, var_0); // Lê valor da bateria
    // ...Temperatura e humidade do ar .............................................................................
    if (DHT.read22(THar) == -2) {   // Lê temperatura e humidade do ar com DHT11
      dtostrf(-999.9, 0, 1, var_6);     // Converte float em string dtostrf(valor,minimo,casas decimais,container)
      dtostrf(-999.9, 0, 1, var_7);     // Converte float em string dtostrf(valor,minimo,casas decimais,container)
    }
    else {
      dtostrf(DHT.temperature, 0, 1, var_6);     // Converte float em string
      // dtostrf(valor,minimo,casas decimais,container)
      dtostrf(DHT.humidity, 0, 1, var_7);        // Converte float em string
    }
        Serial.println("DHT");

    delay(500); // ?? Não sei para que serve

    // ... Sensores de temperatura do solo: 3 sesnores a temperaturas diferentes....................................
    sensorTemperatura1Wire.requestTemperatures();   //envía el comando para obtener las temperaturas
    if (sensorTemperatura1Wire.isConnected(address10)) temp10 = sensorTemperatura1Wire.getTempC(address10); //temperatura em °C do sensor 1
    else temp10 = -999.9;
    dtostrf(temp10, 0, 1, var_1);

    if (sensorTemperatura1Wire.isConnected(address20)) temp20 = sensorTemperatura1Wire.getTempC(address20); //temperatura em °C do sensor 2
    else temp20 = -999.9;
    dtostrf(temp20, 0, 1, var_2);

    if (sensorTemperatura1Wire.isConnected(address30)) temp30 = sensorTemperatura1Wire.getTempC(address30); //temperatura em °C do sensor 3
    else temp30 = -999.9;
    dtostrf(temp30, 0, 1, var_3);

        Serial.println("temp");

    // ...Sensor de radiação solar...................................................................................
    if (als.getALSLux(lux)!=0xFF){
      dtostrf(lux,0,1,var_5);
    }
    else{
      dtostrf(-1, 0, 1, var_5); // Se não possui sensor de luminosidade, o valor da variável é atribuído o valor -1
    }
        Serial.println("lux");

    // ...Sensor de humidade.........................................................................................
    dtostrf(leituraAnalogica(A3), 0, 1, var_4); //sensor de humedad

    // ...Forma payload usando protocolo JSON........................................................................
    strcat(data, "\"cd\":");
    strcat(data, var_0);
    strcat(data, ",\"zz\":");
    strcat(data, var_1);
    strcat(data, ",\"zx\":");
    strcat(data, var_2);
    strcat(data, ",\"zc\":");
    strcat(data, var_3);
    strcat(data, ",\"zv\":");
    strcat(data, var_4);
    strcat(data, ",\"zb\":");
    strcat(data, var_5);
    strcat(data, ",\"al\":");
    strcat(data, var_6);
    strcat(data, ",\"ax\":");
    strcat(data, var_7);
    strcat(data, "\0");
    strcpy(data2send, data);
    Serial.println(data);
    
    // ... Transmite dados ...........................................................................................
    LORA_Send_Data(data2send, bytes2send(data2send), Frame_Counter_Tx);
        Serial.println("enviado");

    Wire.end();  // para resolver el problema de los 1.7V en el modo sleep

    Frame_Counter_Tx++;        // Incrementa frame counter
    sleep_count = 0;           // Reinicia sleep conter
    digitalWrite(NSS, LOW);    // Desativa NSS
    digitalWrite(OE, LOW);     // Desliga Buck-boost
    digitalWrite(EN, LOW);     // Desliga Logic Level Controller
            Serial.println("dorme");
delay(500);
    watchdogOn();

  }
}
