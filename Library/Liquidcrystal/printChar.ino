#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

byte customChar[] = {
  B00000,
  B00000,
  B01110,
  B01000,
  B01000,
  B01000,
  B01000,
  B00000 // costum beat https://maxpromer.github.io/LCD-Character-Creator/ 
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, customChar);
  lcd.home();
  lcd.write(0);
}

void loop() { 
}
