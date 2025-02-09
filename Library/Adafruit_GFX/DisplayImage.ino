#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);
const unsigned char Mybitmap [] PROGMEM = {
//Araay image converter to cpp
};
void setup(){
  display.begin(SSD1306_SWITCHCAPVCC,0x3c);
  delay(2000);
  display.clearDisplay();
  display.drawBitmap(0,0,Mybitmap,128,64,WHITE);
  display.display();
}
