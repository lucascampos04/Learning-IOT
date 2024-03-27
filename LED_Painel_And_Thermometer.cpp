#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32, 16,21);

float temp = 0;
int sensor = (A0);

void setup()
{
  lcd.begin(16,2);
  lcd.backlight();
  lcd.init();
  lcd.clear();
  
}

void loop()
{
	temp = (((analogRead) (sensor) * (5.0) / 1024))-0.5-0.01+0.01;   
    lcd.print(temp);
  	delay(1000);	
    delay(1000);
    
      
  lcd.clear();
}