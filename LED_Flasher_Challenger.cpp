void setup() {
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(6, HIGH); // Acende o LED 6
  digitalWrite(5, LOW);  // Apaga o LED 5
  digitalWrite(4, LOW);  // Apaga o LED 4
  delay(2000);           // Espera 2 segundos

  digitalWrite(6, LOW);  // Apaga o LED 6
  digitalWrite(5, HIGH); // Acende o LED 5
  digitalWrite(4, LOW);  // Apaga o LED 4
  delay(2000);           // Espera 2 segundos

  digitalWrite(6, LOW);  // Apaga o LED 6
  digitalWrite(5, LOW);  // Apaga o LED 5
  digitalWrite(4, HIGH); // Acende o LED 4
  delay(2000);           // Espera 2 segundos
}
