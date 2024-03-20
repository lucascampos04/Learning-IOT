int led = 4;
int led2 = 2;
int led3 = 3;
int pinValor = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop()
{
  pinValor = analogRead(A0); // Lê o valor analógico do pino A0
  Serial.println(pinValor); // Imprime o valor lido no monitor serial

  if (pinValor >= 500 && pinValor < 699) { // Se o valor está entre 500 e 699
    digitalWrite(led, HIGH); // Acende o primeiro LED
    digitalWrite(led2, LOW); // Apaga o segundo LED
    digitalWrite(led3, LOW); // Apaga o terceiro LED
  }
  else if (pinValor >= 700 && pinValor < 999) { // Se o valor está entre 700 e 999
    digitalWrite(led, LOW);  // Apaga o primeiro LED
    digitalWrite(led2, HIGH); // Acende o segundo LED
    digitalWrite(led3, LOW);  // Apaga o terceiro LED
  }
  else if (pinValor >= 1000) { // Se o valor é maior ou igual a 1000
    digitalWrite(led, LOW);  // Apaga o primeiro LED
    digitalWrite(led2, LOW);  // Apaga o segundo LED
    digitalWrite(led3, HIGH); // Acende o terceiro LED
  }
  else { // Se o valor não se encaixa em nenhuma das condições anteriores
    digitalWrite(led, LOW); // Apaga o primeiro LED
    digitalWrite(led2, LOW); // Apaga o segundo LED
    digitalWrite(led3, LOW); // Apaga o terceiro LED
  }
}

