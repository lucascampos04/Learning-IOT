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
  pinValor = analogRead(A0);
  Serial.println(pinValor);

  if (pinValor >= 500 && pinValor < 699){
    digitalWrite(led, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  else if (pinValor >= 700 && pinValor < 999){
    digitalWrite(led, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  }
  else if (pinValor >= 1000){
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
  }
  else {
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
}
