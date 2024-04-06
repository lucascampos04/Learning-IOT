#include <LiquidCrystal_I2C.h>

int fotorresistor = 0;
int sensorInfravermelho = 0;
int led = 10;
int btnJanela = 3;
int btnPorta = 2;
int alarme = 4;
int painelSda = 0;
int painelScl = 0;
int painelVcc = (A0);

bool btnJanelaState = false; 
bool btnPortaState = false;   

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    Serial.begin(9600);
    lcd.begin(16,2);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    pinMode(led, OUTPUT);
    pinMode(alarme, OUTPUT);
    pinMode(sensorInfravermelho, INPUT);
    pinMode(btnPorta, INPUT);
    pinMode(btnJanela, INPUT);
    pinMode(painelSda, OUTPUT);
    pinMode(painelScl, OUTPUT);
}

void AlarmeAndLedOn(){
    digitalWrite(led, HIGH);
    digitalWrite(alarme, HIGH);
}

void AlarmeAndLedOff(){
    digitalWrite(led, LOW);
    digitalWrite(alarme, LOW);
}

void messagePortaOpen(){
    lcd.setCursor(0, 0);
    lcd.print("Porta fechada");
    lcd.setCursor(2, 1);
}

void messageJanelaOpen(){
    lcd.setCursor(0, 0);
    lcd.print("Janela fechada");
    lcd.setCursor(2, 1);
}

void messageInfravermelho(){
    lcd.setCursor(0, 0);
    lcd.print("TE VI");
    lcd.setCursor(2, 1);
}

void loop()
{
    fotorresistor = analogRead(A0);
    sensorInfravermelho = analogRead(A1);

    // Sensor Fotorresistor - Janela
    if (fotorresistor > 500){
        if (digitalRead(btnJanela) == 0){
            messageJanelaOpen();
            AlarmeAndLedOn();
            btnJanelaState = true; // Botão Janela pressionado
        } else if (btnJanelaState) {
            AlarmeAndLedOff(); 
            btnJanelaState = false; // Atualiza o estado do botão Janela
        }
    }

    // Sensor Fotorresistor - Porta
    if (fotorresistor > 500){
        if (digitalRead(btnPorta) == 0){
            messagePortaOpen();
            AlarmeAndLedOn();
            btnPortaState = true; // Botão Porta pressionado
        } else if (btnPortaState) {
            AlarmeAndLedOff(); 
            btnPortaState = false; // Atualiza o estado do botão Porta
        }
    }

    // Sensor infravermelho
    if (fotorresistor > 500){ 
       if (sensorInfravermelho > 1){
            messageInfravermelho();
            AlarmeAndLedOn();
        } else {
            AlarmeAndLedOff();
        }
    }
}
