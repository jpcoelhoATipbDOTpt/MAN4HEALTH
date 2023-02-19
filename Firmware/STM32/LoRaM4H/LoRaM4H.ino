//--------------------------------------------------------------------------- VERSÃO DO FIRMWARE PORTADO PARA O STM32
//
// Neste caso não existe buck-boost nem logic leve converter. A ligação é feita diretamente entre o RFM95 e o STM32.
//
// Numa versão seguinte, será necessário ativar o modo de sleep e o watchdog timer por questões de robustez do código 
//
//-------------------------------------------------------------------------------------------------------------------

#include <SPI.h>
#include "LoRaWAN.h"

// ------------------------------------------------------------------------------------------------------------------
// ALIASES
// ------------------------------------------------------------------------------------------------------------------
#define ledPin PC13

#define ordemFiltro 25 // Ordem do filtro de média

#define periodoDeAmostragem 5000 // Numero de millisegundos associado ao período de amostragem

#define Vbat A0        // Pino usado na medição da tensão da bateria (a partir de divisor resistivo Vbat/2
#define THar 2         // Pino usado na medição da temperatura e humidade do ar com DHT11
// ------------------------------------------------------------------------------------------------------------------
// VARIÁVEIS GLOBAIS
// ------------------------------------------------------------------------------------------------------------------
volatile int sleep_count = 0; // Mantém registo do número de vezes que o MCU acordou desde a última transmissão
const int sleep_total = 1;    // Define o período entre transmissões calculada como sleep_total x 8s.
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

unsigned char data2send[64];
unsigned long amostragem = 0; // Variável utilizada para manter registo do tempo atual
// ------------------------------------------------------------------------------------------------------------------
// OBJETOS
// ------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------
// VETORES DE INTERRUPÇÃO
// ------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------
// WATCHDOG
// ------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------
// SLEEP CONFIG
// ------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------
// INICIALIZA MCU
// ------------------------------------------------------------------------------------------------------------------
void setup() {

  pinMode(SS, OUTPUT);                   // Configura pinos de I/O para comunicação com RFM95
  digitalWrite(SS, LOW);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  SPI.setDataMode(SPI_MODE0);            // Inicializa comunicação SPI com RFM95
  SPI.setClockDivider(SPI_CLOCK_DIV16);  // Força a que o clock do SPI seja 72 MHz/16 = 4.5 MHz
  SPI.begin();                           //
  
  amostragem = millis();
}
// ------------------------------------------------------------------------------------------------------------------
// CALCULA O NUMERO DE CARATERES NA MENSAGEM A ENVIAR
// ------------------------------------------------------------------------------------------------------------------
int bytes2send(unsigned char *data)
{
  int i=0;
  while(data[i]!='\0') i++;
  return i;
}
// ------------------------------------------------------------------------------------------------------------------
// AQUISIÇÃO e TRANSMISSÃO
// ------------------------------------------------------------------------------------------------------------------
void loop() {
  if ((millis()-amostragem) >= periodoDeAmostragem) {  // Depos de acordado verifica se já é hora de transmitir
    char data[50] = "\0";
    
    digitalWrite(NSS, HIGH);    // Ativa NSS
    delay(100);                 // Aguarda por estabilização da tensão

    //digitalWrite(SS, LOW);    // Ativa NSS
    RFM_Init();                 // Inicializa RFM95
    
    dtostrf(345.5,0,1,var_0); // Valor arbitrário

    // Forma payload usando protocolo JSON.
    strcat(data,"\"cd\":");
    strcat(data,var_0);
    strcat(data,"\0");
    strcpy((char *)data2send,data);

    LORA_Send_Data(data2send, bytes2send(data2send), Frame_Counter_Tx); // Transmite dados
    
    Frame_Counter_Tx++; // Incrementa frame counter
    digitalWrite(NSS, LOW);    // Desativa NSS
    //digitalWrite(SS, HIGH);    // Desativa NSS

    digitalWrite(ledPin, LOW);
    delay(500);
    digitalWrite(ledPin, HIGH);
    amostragem = millis();

    
  }
}
