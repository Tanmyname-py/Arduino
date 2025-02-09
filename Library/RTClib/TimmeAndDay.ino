#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>
RTC_DS1307 rtc;

char Hari[7][12] = {"MINGGU","SENIN","SELASA","RABU","KAMIS","JUM'AT","SABTU"};

void setup(){
  Serial.begin(9600);
  if (! rtc.begin()){
    Serial.println("Terjadi masalah pada rtc");
    while (1);
  }
  if (rtc.isrunning()){
    Serial.println("Rtc tidak bekerja mohon setel ulang waktu");
    rtc.adjust(DateTime(2025, 2, 8, 10, 23, 0));
  }
  Serial.println("Test modul rtc DS1307");
}

void loop(){
  DateTime now = rtc.now();
  int offset = 7 * 3600;
  DateTime localTime = now + TimeSpan(offset);
  // Serial.print(Hari[now.dayOfTheWeek()]);
  // Serial.print(", ");
  // Serial.print(now.day(), DEC); Serial.print('/');
  // Serial.print(now.month(),DEC); Serial.print('/');
  // Serial.print(now.year(),DEC); Serial.print('/');
  //Waktu
  Serial.print(now.hour(),DEC); Serial.print(":");
  Serial.print(now.minute(),DEC); Serial.print(":");
  Serial.print(now.second(),DEC); Serial.println();
}