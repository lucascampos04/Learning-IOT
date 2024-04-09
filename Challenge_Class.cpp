#include <LiquidCrystal_I2C.h>

// Definição dos pinos utilizados
int led = 10;
int btnJanela = 3;
int btnPorta = 2;
int alarme = 4;

// Variáveis para armazenar o estado dos sensores
bool janelaAberta = false;
bool portaAberta = false;
bool movimentoDetectado = false;

// Variáveis para controle do estado do sistema
bool dia = false;
bool tocarAlarme = false;
int lastMessage = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(9600);

    // Inicialização e configuração do display LCD
    lcd.begin(16, 2);
    lcd.init();
    lcd.backlight();
    lcd.clear();

    // Configuração dos pinos como entrada ou saída
    pinMode(led, OUTPUT);
    pinMode(alarme, OUTPUT);
    pinMode(btnPorta, INPUT);
    pinMode(btnJanela, INPUT);
}

// Função para exibir mensagem de alarme desligado no LCD
void messageAlarmeDesligado() {
    // Limpa o LCD se a última mensagem não foi a de alarme desligado
    if (lastMessage != 1)
        lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Alarme desligado");
    lastMessage = 1;
}

// Função para exibir o estado da porta no LCD
void messagePorta(bool open) {
    String message;

    // Define a mensagem com base no estado da porta
    if (open)
        message = "Porta  aberta   ";
    else
        message = "Porta  fechada  ";

    // Exibe a mensagem no LCD
    lcd.setCursor(0, 1);
    lcd.print(message);
}

// Função para exibir o estado da janela no LCD
void messageJanela(bool open) {
    String message;

    // Define a mensagem com base no estado da janela
    if (open)
        message = "Janela aberta  ";
    else
        message = "Janela fechada ";

    // Limpa o LCD se a última mensagem não foi a do estado da janela
    if (lastMessage != 2)
        lcd.clear();

    // Exibe a mensagem no LCD
    lcd.setCursor(0, 0);
    lcd.print(message);
    lastMessage = 2;
}

// Função para exibir o estado do sensor de movimento no LCD
void messageInfravermelho(bool detectado) {
    // Limpa o LCD se a última mensagem não foi a do sensor de movimento
    if ((lastMessage != 3 && detectado) || (lastMessage != 4 && !detectado))
        lcd.clear();

    // Exibe a mensagem no LCD de acordo com o estado do sensor de movimento
    lcd.setCursor(0, 0);
    lcd.print("Sensor Movimento");

    if (detectado) {
        lcd.setCursor(0, 1);
        lcd.print("Detectado");
        lastMessage = 3;
    } else {
        lcd.setCursor(0, 1);
        lcd.print("Ativado");
        lastMessage = 4;
    }
}

// Função para ativar o alarme
void soarAlarme(bool ligado) {
    digitalWrite(led, ligado);
    digitalWrite(alarme, ligado);
}

void loop() {
    // Tocar os alarmes.
    soarAlarme(tocarAlarme);

    // Verificar se está de dia.
    bool dia = analogRead(A0) < 500;

    if (dia) {
        tocarAlarme = false;
        // Mostrar informações no LCD.
        messageAlarmeDesligado();
        return;
    }

    // Verificar se a porta e janela estão abertas.
    janelaAberta = digitalRead(btnJanela) != 0;
    portaAberta = digitalRead(btnPorta) != 0;

    if (!janelaAberta || !portaAberta) {
        // Mostrar informações no LCD.
        messageJanela(janelaAberta);
        messagePorta(portaAberta);
        tocarAlarme = false;
        return;
    }

    // Detectar movimento usando o PIR.
    movimentoDetectado = analogRead(A1) > 1;

    // Exibir o estado do sensor de movimento no LCD e controlar o alarme
    messageInfravermelho(movimentoDetectado);
    tocarAlarme = movimentoDetectado;
}
