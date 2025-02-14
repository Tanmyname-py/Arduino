#include <Wire.h>
#include <RTClib.h>
#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#include <Servo.h> 
Servo myservo;
RTC_DS1307 rtc;
#define Lebar_Screen 128
#define Tinggi_Screen 64
int pos = 0;

Adafruit_SSD1306 display(Lebar_Screen,Tinggi_Screen,&Wire,-1);
char Hari[7][12] = {"MINGGU","SENIN","SELASA","RABU","KAMIS","JUM'AT","SABTU"};

void setup(){
  Serial.begin(9600);
   display.begin(SSD1306_SWITCHCAPVCC,0x3c);
   myservo.attach(11);
   delay(2000);
   display.clearDisplay();
  if (! rtc.begin()){
    Serial.println("Terjadi masalah pada rtc");
    while (1);
  }
  if (rtc.isrunning()){
    Serial.println("RTC IS RUNNING SETUP TIME NOW ");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2025, 2, 14, 9, 59, 0));
  }
  Serial.println("Test modul rtc DS1307");
}


void loop() {
  // put your main code here, to run repeatedly:
   DateTime now = rtc.now();
  int offset = 7 * 3600;
  DateTime localTime = now + TimeSpan(offset);
  // Serial.print(Hari[now.dayOfTheWeek()] );
  // Serial.print(", ");
  // Serial.print(now.day(), DEC); Serial.print('/');
  // Serial.print(now.month(),DEC); Serial.print('/');
  // Serial.print(now.year(),DEC); Serial.print('/');
  //Waktu
  // Serial.print(localTime.hour()+1,DEC); Serial.print(":");
  Serial.print(localTime.minute(),DEC); Serial.print(":");
  Serial.print(localTime.second(),DEC); Serial.println();
  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(32,28);
  // display.print(localTime.hour()+1,DEC);
  // display.print(":");
  display.print(localTime.minute(),DEC);
  // display.print(":");
  // display.print(localTime.second(),DEC);
  // display.display();
  // display.clearDisplay();
  if(localTime.hour(),DEC >=6){
    myservo.write(pos);
    myservo.write(pos+90);
    delay(1000);
  }
}
