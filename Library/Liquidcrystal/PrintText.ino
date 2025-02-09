#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f,16,2);

void setup(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("HELLO WORLD");
  lcd.setCursor(1,1);
  lcd.print("From LiquidCrystal");
}
void loop(){
  
}
