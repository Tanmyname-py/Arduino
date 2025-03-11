#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>
#define Width 128
#define Height 64
#define T D5
#define E D6
#define Maks 200
Adafruit_SSD1306 display(Width,Height,&Wire,-1);
NewPing us (T,E,Maks);
int jarak;
char val_jarak[3];
void setup(){
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC,0x3c);
  display.clearDisplay();
}
void loop(){
  jarak = us.ping_cm();
  sprintf(val_jarak,"%3d",jarak);
  Serial.println("Jarak : " + String(jarak) + " cm");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(1,1);
  display.print("Jarak (cm)");
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(5,25);
  display.print(val_jarak);
  display.println(" cm");
  display.display();
  display.clearDisplay();
}
