#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int col = 16 ; //colom
const int row = 2;  // baris
int position = 0;
LiquidCrystal lcd(0x27,col,row);

void setup(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(col,row); //Kolom dan baris 
  lcd.clear();
}
void loop(){
  lcd.clear();
  position +=1;
  lcd.setCursor(position,1);
  if ( position < 0 || position >= col){
    position = 0;
  }
}

