#include <SPI.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include "LoRaWAN.h"
// ------------------------------------------------------------------------------------------------------------------
// ALIASES
// ------------------------------------------------------------------------------------------------------------------
#define LED  6        // LED que pode ser utilizado para DEBUG (ativo baixo)
#define OE   5        // Ativa/desativa logic level converter
#define EN   4        // Ativa/desativa buck-boost para +3V3
#define ordemFiltro 5 // Ordem do filtro de média
// ------------------------------------------------------------------------------------------------------------------
// VARIÁVEIS GLOBAIS
// ------------------------------------------------------------------------------------------------------------------
volatile int sleep_count = 0; // Mantém registo do número de vezes que o MCU acordou desde a última transmissão
const int sleep_total = 8;    // Define o período entre transmissões calculada como sleep_total x 8s.
                              // Para 1 hora => sleep_total = 450. Poderá ser necessário alterar o valor do prescale
                              // do WDT para outros intervalos de tempo. Por exemplo, se o ciclo de trabalho for 1
                              // minuto, na atual condição, sleep_total = 7.5 o que não é possível dado que sleep_
                              // _total deve ser inteiro. No entanto, ajustando o WDT para 1 segundo, sleep_total=60       
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
  // Começa por fazer o reset ao watchdog
  MCUSR &= ~(1 << WDRF); 
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
  wdt_reset();
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
  SPI.setDataMode(SPI_MODE0); // Inicializa comunicação SPI com RFM95
  SPI.begin();                //
  pinMode(NSS, OUTPUT);       // Configura pinos de I/O para comunicação com RFM95
  pinMode(DIO0, INPUT);       //
  pinMode(OE,OUTPUT);         // Configura pinos para habilitar conversores DC/DC
  pinMode(EN,OUTPUT);         //
  digitalWrite(NSS, LOW);    // Ativa NSS
  digitalWrite(OE,LOW);      // Liga Buck-boost
  digitalWrite(EN,LOW);      // Liga Logic Level Controller
  delay(100);                 // Aguarda por estabilização da tensão
  watchdogOn();               // Configura e ativa watchdog

}
// ------------------------------------------------------------------------------------------------------------------
// AQUISIÇÃO e TRANSMISSÃO
// ------------------------------------------------------------------------------------------------------------------
void loop() {
  goToSleep(); // Entra em suspensão
  if (sleep_count >= sleep_total) {  // Depos de acordado verifica se já é hora de transmitir
    digitalWrite(NSS, HIGH);    // Ativa NSS
    digitalWrite(OE,HIGH);      // Liga Buck-boost
    digitalWrite(EN,HIGH);      // Liga Logic Level Controller
    delay(100); 
    RFM_Init();                 // Inicializa RFM95
    // Aguarda por estabilização da tensão
    char Data[6]="Hello";
    uint8_t Data_Length = 6;
    LORA_Send_Data(Data, Data_Length, Frame_Counter_Tx); // Transmite dados
    Frame_Counter_Tx++; // Incrementa frame counter
    sleep_count = 0;  // Reinicia sleep conter
    digitalWrite(NSS, LOW);    // Ativa NSS
    digitalWrite(OE,LOW);      // Liga Buck-boost
    digitalWrite(EN,LOW);      // Liga Logic Level Controller
  }
}
