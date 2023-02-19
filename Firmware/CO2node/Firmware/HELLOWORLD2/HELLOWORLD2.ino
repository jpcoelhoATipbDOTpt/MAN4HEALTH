// HELLO WORLD para a placa CO2
// Testa hardware
//
// Projeto MAN4HEALTH
//
// (c)2023 jpcoelho

#define LED PD6 // LED ligado ao pino 12 do ATMEGA328 (PD6)
                // Configuração ativa-baixa
void setup() {
  // Define LED como saída
  pinMode(LED, OUTPUT);
  Serial.begin(250000); // Para um Fosc = 8MHz, baudrate = 250,000 bps => erro = 0%
                        // http://wormfood.net/avrbaudcalc.php?bitrate=300%2C600%2C1200%2C2400%2C4800%2C9600%2C14.4k%2C19.2k%2C28.8k%2C38.4k%2C57.6k%2C76.8k%2C115.2k%2C230.4k%2C250k%2C460.8k%2C.5m%2C921.6k%2C1m&clock=8&databits=8
}

void loop() {
  Serial.println("M*A*N*4*H*E*A*L*T*H"); // Envia string via porto série
  digitalWrite(LED, HIGH);               // desliga LED
  delay(1000);                           // aguarda 1 segundo
  digitalWrite(LED, LOW);                // liga LED
  delay(1000);                           // aguarda 1 segundo
}
