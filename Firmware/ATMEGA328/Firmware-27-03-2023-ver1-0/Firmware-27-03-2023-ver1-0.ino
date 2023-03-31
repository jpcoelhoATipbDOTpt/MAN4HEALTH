/*
 * Variables del código
 * 
 * cd = var_0 = batería
 * zz = var_1 = temperatura del suelo 10cm
 * zx = var_2 = temperatura del suelo 20cm   -> RECORDAR IDENTIFICARLOS BIEN ANTES DE PONERLOS EN LA ESTACA
 * zc = var_3 = temperatura del suelo 30cm
 * zv = var_4 = humedad del suelo
 * zb = var_5 = lux      -> SDA - A4
 *                       -> SCL - A5
 * al = var_6 = temperatura del aire (DHT22)
 * ax = var_7 = humedad del aire (DHT22)
 * 
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
const int sleep_total = 1;   //1 -> 10s   // Define o período entre transmissões calculada como sleep_total x 8s.
                              // Para 1 hora => sleep_total = 450. Poderá ser necessário alterar o valor do prescale
                              // do WDT para outros intervalos de tempo. Por exemplo, se o ciclo de trabalho for 1
                              // minuto, na atual condição, sleep_total = 7.5 o que não é possível dado que sleep_
                              // _total deve ser inteiro. No entanto, ajustando o WDT para 1 segundo, sleep_total=60
char var_0[8]={"\0"};         // Leitura da A/D 0 (Tensão da bateria)
char var_1[8]={"\0"};         // Leitura da A/D 1 (Genérico)
char var_2[8]={"\0"};         // Leitura da A/D 2 (Genérico)
char var_3[8]={"\0"};         // Leitura da A/D 3 (Genérico)
char var_4[8]={"\0"};         // Leitura da A/D 4 (Genérico)
char var_5[8]={"\0"};         // Leitura da A/D 5 (Genérico)
char var_6[8]={"\0"};         // Leitura da temperatura (DTH@PD2)
char var_7[8]={"\0"};         // Leitura da humidade relativa (DTH@PD2)     

char data2send[150];

float lux;
int lectura = 0; //bandera para asegurar la correcta lectura de los sensores
int contador = 0; //para limitar el tiempo que espera respuesta del sensor

// ------------------------------------------------------------------------------------------------------------------
// OBJETOS
// ------------------------------------------------------------------------------------------------------------------
dht DHT;
VEML7700 als;

OneWire ourWire(16);                //Se establece el pin analógico 2 como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

DeviceAddress address10 = {0x28, 0x1B, 0xB2, 0x74, 0x4, 0x0, 0x0, 0x49}; //dirección del sensor 1
DeviceAddress address20 = {0x28, 0x45, 0x99, 0x75, 0x4, 0x0, 0x0, 0x73}; //dirección del sensor 2 
DeviceAddress address30 = {0x28, 0x85, 0xEF, 0x36, 0x4, 0x0, 0x0, 0x75}; //dirección del sensor 3


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
  WDTCSR = (1<<WDCE)|(1<<WDE);
  // Inicia watchdog timer com prescaler (8 segundos) WDP3:WDP0 = "1001"
  // WDIW: Watchdog Interrupt Enable - Se WDE = 0 o watchdog está em modo  
  //                                   interrupção e se WDE=1 está em modo
  //                                   interrução + reset
  // WDTCSR = (1<<WDIE)|(1<<WDP3)|(1<<WDP0); //(8 segundos)
  WDTCSR = (1<<WDIE)|(1<<WDP3)|(1<<WDP0);
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
  WDTCSR |= (1<<WDCE)|(1<<WDE);
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
  //Serial.begin(9600);    // Debug
  sensors.begin();   //Se inicia el sensor
    
  SPI.setDataMode(SPI_MODE0); // Inicializa comunicação SPI com RFM95
  SPI.begin();                //
  pinMode(NSS, OUTPUT);       // Configura pinos de I/O para comunicação com RFM95
  pinMode(DIO0, INPUT);       //
  pinMode(OE,OUTPUT);         // Configura pinos para habilitar conversores DC/DC
  pinMode(EN,OUTPUT);         //
  
  pinMode(LED, OUTPUT);
  digitalWrite(LED,HIGH);
  
  digitalWrite(NSS, LOW);     // Ativa NSS
  digitalWrite(OE,LOW);       // Liga Buck-boost
  digitalWrite(EN,LOW);       // Liga Logic Level Controller     
  delay(100);                 // Aguarda por estabilização da tensão
  analogReference(EXTERNAL);  // Estabelece tensão de referência da ADC como externo
  watchdogOn();               // Configura e ativa watchdog
  
}
// ------------------------------------------------------------------------------------------------------------------
// leitura com filtro passa-baixo
// ------------------------------------------------------------------------------------------------------------------
float leituraAnalogica(const byte port)
{
  ADCSRA |= _BV(ADEN);   // Ativa ADC
  float valorFiltrado = 0;
  for (int i=0;i<ordemFiltro;i++) {
    valorFiltrado += (float)analogRead(port);
    delayMicroseconds(50);
  }
  ADCSRA &= ~_BV(ADEN); // Desativa ADC
  // Filtro de média...
  return(valorFiltrado/(float)ordemFiltro);
}

// ------------------------------------------------------------------------------------------------------------------
// CALCULA O NUMERO DE CARATERES NA MENSAGEM A ENVIAR
// ------------------------------------------------------------------------------------------------------------------
int bytes2send(char *data)
{
  int i=0;
  while(data[i]!='\0') i++;
  return i;
}

// ------------------------------------------------------------------------------------------------------------------
// AQUISIÇÃO e TRANSMISSÃO
// ------------------------------------------------------------------------------------------------------------------
void loop() {
  goToSleep(); // Entra em suspensão
  if (sleep_count >= sleep_total) {  // Depois de acordado verifica se já é hora de transmitir
    watchdogOff();
    char data[200]="\0";
    
    digitalWrite(NSS, HIGH);    // Ativa NSS
    digitalWrite(OE,HIGH);      // Liga Buck-boost
    digitalWrite(EN,HIGH);      // Liga Logic Level Controller
    delay(5000);                // Aguarda por estabilização da tensão (necessário para o DHT11)
    
    RFM_Init();                 // Inicializa RFM95

    dtostrf(leituraAnalogica(Vbat),0,1,var_0); // Lê valor da bateria
    //dtostrf(leituraAnalogica(A1),0,1,var_1);   // Lê ADC1
    //dtostrf(leituraAnalogica(A2),0,1,var_2);   // Lê ADC2
    //dtostrf(leituraAnalogica(A3),0,1,var_3);   // Lê ADC3
    //dtostrf(leituraAnalogica(A4),0,1,var_4);   // Lê ADC4     
    //dtostrf(leituraAnalogica(A5),0,1,var_5);   // Lê ADC5

    //Serial.println("Inicio de lectura de los sensores");
    
//----------------------------------------
//             Lectura DHT22                --> modificar en la condicion del if 11 -> 22
//----------------------------------------
    while (lectura == 0){
      if(DHT.read22(THar)!=-2){
        dtostrf(DHT.temperature,0,1,var_6);        // Converte float em string dtostrf(valor,minimo,casas decimais,container)
        dtostrf(DHT.humidity,0,1,var_7);           // Converte float em string dtostrf(valor,minimo,casas decimais,container)
        lectura = 1;
      }
      else{
        if(contador==500){
          dtostrf(99999,0,1,var_6);
          dtostrf(99999,0,1,var_7);
          lectura = 1;
        }
      }
      contador++;
    }

    contador = 0;
    lectura = 0;
    
//----------------------------------------
//    Lectura Sensores de temperatura
//----------------------------------------
    while(lectura==0){
    sensors.requestTemperatures();   //envía el comando para obtener las temperaturas
    float temp10= sensors.getTempC(address10);//Se obtiene la temperatura en °C del sensor 1
    float temp20= sensors.getTempC(address20);//Se obtiene la temperatura en °C del sensor 2
    float temp30= sensors.getTempC(address30);//Se obtiene la temperatura en °C del sensor 3    

// ------ Temperatura nivel 1 --------   
    if(temp10 != -127 && temp10 != 85){
      dtostrf(temp10,0,1,var_1);
    }
    else{
      if(contador == 500){
        temp10 = 99999;
        dtostrf(temp10,0,1,var_1); 
      }
    }
// ------ Temperatura nivel 2 --------       
    if(temp20 != -127 && temp20 != 85){
      dtostrf(temp20,0,1,var_2);
    }
    else{
      if(contador == 500){
        temp20 = 99999;
        dtostrf(temp20,0,1,var_2);
      }
    }
// ------ Temperatura nivel 3 --------    
    if(temp30 != -127 && temp30 != 85){
      dtostrf(temp30,0,1,var_3);
    } 
    else{
      if(contador == 500){
        temp30 = 99999;
        dtostrf(temp30,0,1,var_3);
      }
    }
    
    if ((temp10 != -127 && temp20 != -127 && temp30 != -127) && (temp10 != 85 && temp20 != 85 && temp30 != 85)){ 
      lectura = 1;
      }
      
    contador++;
    }

    contador = 0;
    lectura = 0;
    
//----------------------------------------
//           Lectura VEML7700
//----------------------------------------
    while(lectura==0){
      als.begin();
      als.getALSLux(lux);
      if (lux != 0){
        dtostrf(lux,0,1,var_5);
        lectura = 1;
      }
      else{
        if(contador==1000){
          dtostrf(99999,0,1,var_5);
          lectura = 1;
        }
      }
      contador ++;
    }

    contador = 0;
    lectura = 0;
    
//----------------------------------------
//        Lectura sensor de humedad
//----------------------------------------
    dtostrf(leituraAnalogica(A3),0,1,var_4); //sensor de humedad
    
   
    // Forma payload usando protocolo JSON.
    strcat(data,"\"cd\":");
    strcat(data,var_0);
    strcat(data,",\"zz\":");
    strcat(data,var_1);
    strcat(data,",\"zx\":");
    strcat(data,var_2);
    strcat(data,",\"zc\":");
    strcat(data,var_3);
    strcat(data,",\"zv\":");
    strcat(data,var_4);
    strcat(data,",\"zb\":");
    strcat(data,var_5);
    strcat(data,",\"al\":");
    strcat(data,var_6);
    strcat(data,",\"ax\":");
    strcat(data,var_7);
    strcat(data,"\0");
    strcpy(data2send,data);
    Serial.print(data2send);
    Serial.print("->");
    Serial.println(bytes2send(data2send));
    
    LORA_Send_Data(data2send, bytes2send(data2send), Frame_Counter_Tx); // Transmite dados
    
    //Serial.println("Paquete enviado");

    Wire.end();  // para resolver el problema de los 1.7V en el modo sleep
    
    Frame_Counter_Tx++; // Incrementa frame counter
    sleep_count = 0;  // Reinicia sleep conter
    digitalWrite(NSS, LOW);    // Desativa NSS
    digitalWrite(OE,LOW);      // Desliga Buck-boost
    digitalWrite(EN,LOW);      // Desliga Logic Level Controller
    watchdogOn();
  }

}
