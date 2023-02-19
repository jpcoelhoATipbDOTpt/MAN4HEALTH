#include <SoftwareSerial.h>
#include <TinyRS485.h>
#include <TinyModbus.h>
//
#define MAX485_DE 4
#define MAX485_RE 5
#define MAX485_RO 2
#define MAX485_DI 3
//
#define TIMEOUT 100
#define FRAMELGTH 8
#define MYID 69
#define LIMITADD 0x000E

int bufcnt=0; 
const int BUFFER_SIZE = 10;
uint8_t   RX[BUFFER_SIZE]={0,0,0,0,0,0,0,0,0,0}; // Buffer com a mensagem recebida do master
uint8_t   TX[BUFFER_SIZE]={0,0,0,0,0,0,0,0,0,0}; // Buffer com a mensagem de retorno para o master
int       TxLen = 0;                             // Dimensão da mensagem a enviar
uint16_t  CRC = 0x0000;                          // CRC da mensagem a enviar
uint16_t  BaseAddress = 0x0000;                  // Endereço base solicitado pelo Master
uint16_t  OfftAddress = 0x0000;                  // Offser associado ao endereço solicitado pelo Master

unsigned long myTime;

int i = 0; // Índice genérico usado em ciclos FOR

SoftwareSerial SoftSerial(MAX485_RO,MAX485_DI); // RX, TX
TinyRS485 RS485;

// ------------------------------------------------------------------------------------------------------------------
// MÁQUINA DE ESTADOS PRINCIPAL
// ------------------------------------------------------------------------------------------------------------------
enum estadosistema{
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
  ERRORFRAME  // Responde com um erro
} estado=WAIT4FRAME;

// ------------------------------------------------------------------------------------------------------------------
// bool checkForFrame(void)
// ------------------------------------------------------------------------------------------------------------------
bool checkForFrame()
{
  bufcnt=0;
  if (RS485.available())
  {
    myTime = millis();
    RX[bufcnt]=RS485.receive();
    bufcnt++;
    // Baudrate = 115200 bps, 80 bits => 0.7 ms para receber a frame Modbus
    while((millis()-myTime)<TIMEOUT)
    {
      if (RS485.available())
      {
         RX[bufcnt]=RS485.receive();
         bufcnt++;
      }
    }
  }
  // O tempo terminou desde que foi recebido o primeiro caracter... verificar se a frame completa foi recebida
  if (bufcnt>=FRAMELGTH) return(true);
  else return(false);
}

// ------------------------------------------------------------------------------------------------------------------
// void setup(void)
// ------------------------------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(1000000);
  SoftSerial.begin(115200); // Porto série (software) usado pelo transceiver RS485
  
  pinMode(MAX485_DE,OUTPUT);
  pinMode(MAX485_RE,OUTPUT);
  
  RS485.begin(SoftSerial,MAX485_DE,MAX485_RE);
}

// ------------------------------------------------------------------------------------------------------------------
// void loop(void)
// ------------------------------------------------------------------------------------------------------------------
void loop()
{
 // ...................................................................................................
 // Máquina de estados
 // ...................................................................................................
 switch(estado)
 {
    // .................................................................................................
    case SETRCVMODE:
                  Serial.println("SET MODE");
                  digitalWrite(MAX485_DE,LOW); // Desativa DRIVER
                  digitalWrite(MAX485_RE,LOW); // Ativa RECEIVER
                  estado = WAIT4FRAME;
                  break;
    // .................................................................................................
    case WAIT4FRAME:
                  if (checkForFrame()) estado = TSTINFRAME;
                  break;
    // .................................................................................................
    case TSTINFRAME:
                  // Verifica integridade...
                  // TDU[0]^=0x01; // Simula erro de transmissão
                  if(compute_crc(RX,bufcnt-1)==0){ // CRC OK
                    // Verifica se a frame é para mim...
                    if(RX[0]== MYID){
                      estado = MESSAGE4ME; // Sim, sou eu...
                    }
                    else{
                      estado = WAIT4FRAME; // Nop, aguarda por nova frame...
                    }
                  }
                  else{ // ERRO DE TRANSMISSÂO
                    estado = ERRORFRAME;
                  }   
                  break;
    // .................................................................................................                  
    case MESSAGE4ME:
                  // Verifica se o slave pode realizar a função solicitada em RX[1]
                  switch(RX[1]) {
                    case 0x03:  estado=RDFUNCTION;
                                break;
                    case 0x04:  estado=WEFUNCTION;
                                break;
                    default:    estado=FUNCNERROR;
                                break;                                                             
                  }
                  break;
    // .................................................................................................                  
    case RDFUNCTION:
                  // Verifica se o endereço está dentro dos limites solicitados
                  BaseAddress = (((uint16_t)RX[2])<<8)+((uint16_t)RX[3]); // Calcula endereço base
                  OfftAddress = (((uint16_t)RX[4])<<8)+((uint16_t)RX[5]); // Calcula offset
                  if (BaseAddress+OfftAddress>LIMITADD){
                    estado = ADDREERROR;
                  }
                  else {
                    estado = DECODE4RDE; // Descodifica pedido de leitura
                  }
                  break;
    // .................................................................................................                  
    case WEFUNCTION:
                  // Verifica se o endereço está dentro dos limites solicitados
                  BaseAddress = (((uint16_t)RX[2])<<8)+((uint16_t)RX[3]); // Calcula endereço base
                  OfftAddress = (((uint16_t)RX[4])<<8)+((uint16_t)RX[5]); // Calcula offset
                  if (BaseAddress+OfftAddress>LIMITADD){
                    estado = ADDREERROR;
                  }
                  else {
                    estado = DECODE4WTE; // Descodifica pedido de escrita
                  }
                  break;                  
    // .................................................................................................
    case FUNCNERROR:
                  // Constroi frame
                  TX[0] = MYID;
                  TX[1] = RX[1] + 0x80;
                  TX[2] = 0x01;
                  TxLen = 3;
                  estado = ANSWERFRME;               
                  break;
    // .................................................................................................
    case ADDREERROR:
                  // Constroi frame
                  TX[0] = MYID;
                  TX[1] = RX[1] + 0x80;
                  TX[2] = 0x02;
                  TxLen = 3;
                  estado = ANSWERFRME;       
                  break;
    // .................................................................................................
    case DECODE4RDE:
                  // Coleta a informação necessária para originar a resposta
                  // Constroi frame
                  TX[0] = MYID;
                  TX[1] = RX[1];
                  TX[2] = 0x02;
                  TX[3] = 0x02;
                  TX[4] = 
                  TxLen = 5;                
                  estado = WAIT4FRAME;
                  break;              
    // .................................................................................................                  
    case ANSWERFRME:
                  // Adiciona CRC à frame
                  CRC   = compute_crc(TX,TxLen);
                  TX[TxLen++] = (uint8_t) CRC;
                  TX[TxLen++] = (uint8_t) (CRC>>8);
                  // Ativa MAX485 para TX
                  digitalWrite(MAX485_DE,HIGH); // Ativa DRIVER
                  digitalWrite(MAX485_RE,HIGH); // Desativa RECEIVER
                  // Transmite dados...
                  for(i=0;i<TxLen;i++) RS485.transmit(TX[i]);
                  estado=SETRCVMODE;
                  break;
    // .................................................................................................                  
    case ERRORFRAME:   
                  Serial.println("ERRO");
                  estado = SETRCVMODE;
                  break;
    // .................................................................................................
  }
}
