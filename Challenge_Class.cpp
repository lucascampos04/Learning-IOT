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

void setup()
{
    //Serial.begin(9600);

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
void messageSensores(bool ligado)
{
    // Limpa o LCD se a última mensagem não foi a de alarme desligado
    if ((lastMessage != 1 && ligado) || (lastMessage != 2 && !ligado))
        lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Sensores");
  	lcd.setCursor(0, 1);
  	
  	if(ligado)
    {
  		lcd.print("ativados");
      	lastMessage = 1;
      	return;
    }
  
	lcd.print("desativados");
	lastMessage = 2;
}

void messageAlarme(int index)
{
  	// Limpa o LCD se a última mensagem não foi do mesmo sensor.
    if (lastMessage != 3 + index)
        lcd.clear();
  
  	// Exibe a mensagem no LCD de acordo com o estado do sensor.
    lcd.setCursor(0, 0);
    lcd.print("Alarme acionado");
  	lcd.setCursor(0, 1);
  	
  	String sensores[] = {"Janela","Porta","Corredor"};
  	lcd.print(sensores[index]);
  
  	lastMessage = 3 + index;
}

// Função para ativar o alarme
void soarAlarme(bool ligado)
{
  	digitalWrite(led, ligado);
  	
  	if(!ligado)
    {
      	noTone(alarme);
      	return;
    }
	
  	int tones[] = {460, 500, 600};
	for(int i = 0; i < 3; i++)
	{
		float time = 100;
		tone(alarme, tones[i], time);
		Serial.println(tones[i]);
      	delay(time);
	} 	
}

void loop()
{
    // Tocar os alarmes.
    soarAlarme(tocarAlarme);

    // Verificar se está de dia.
    bool dia = analogRead(A0) < 500;

    if (dia)
    {
      	messageSensores(false);
        return;
    }

    // Verificar se a porta e janela estão abertas.
    janelaAberta = digitalRead(btnJanela) == 0;
    portaAberta = digitalRead(btnPorta) == 0;

    if (janelaAberta)
        messageAlarme(0);
  
  	if (portaAberta)
     	messageAlarme(1);

    // Detectar movimento usando o PIR.
    movimentoDetectado = analogRead(A1) > 1;

    if(movimentoDetectado)
    	messageAlarme(2);
  
    // Tocar o alarme.
  	tocarAlarme = movimentoDetectado || portaAberta || janelaAberta;
  	
  	if(tocarAlarme)
      	return;
  
  	messageSensores(true);
}