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

}

void loop() {
  digitalWrite(LED, HIGH);               // desliga LED
  delay(1000);                           // aguarda 1 segundo
  digitalWrite(LED, LOW);                // liga LED
  delay(1000);                           // aguarda 1 segundo
}
