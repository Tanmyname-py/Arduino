#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>

#define Lebar_Screen 128
#define Tinggi_Screen 64

Adafruit_SSD1306 display(Lebar_Screen,Tinggi_Screen,&Wire,-1);

void setup(){
  display.begin(SSD1306_SWITCHCAPVCC,0x3c);
  delay(2000);
  display.clearDisplay();
  //display Text 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,28);
  display.println("Hello World");
  display.display();

  //Running Text
  display.startscrollright(0x00,0x07);
}
void loop(){
  
}
