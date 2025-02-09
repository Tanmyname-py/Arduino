#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);

  // Cek apakah RTC terhubung
  if (!rtc.begin()) {
    Serial.println("Tidak dapat menemukan RTC!");
    while (1);
  }

  // Cek apakah RTC kehilangan waktu
  if (rtc.lostPower()) {
    Serial.println("RTC kehilangan daya, setting ulang waktu...");
    // Atur waktu saat pertama kali dijalankan
    // Gunakan waktu UTC (misalnya, 2025-02-08 12:00:00 UTC)
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // Untuk mengatur waktu manual:
    // rtc.adjust(DateTime(2025, 2, 8, 12, 0, 0)); // 8 Februari 2025, 12:00:00 UTC
  }

  // Set zona waktu UTC+7 (untuk WIB)
  // Misalnya, waktu saat ini UTC 12:00:00 harus diubah menjadi 19:00:00
  DateTime now = rtc.now();
  int offset = 7 * 3600;  // 7 jam dalam detik (UTC+7)
  DateTime localTime = now + TimeSpan(offset);

  // Menampilkan waktu lokal
  Serial.print("Waktu Lokal: ");
  Serial.print(localTime.year(), DEC);
  Serial.print('/');
  Serial.print(localTime.month(), DEC);
  Serial.print('/');
  Serial.print(localTime.day(), DEC);
  Serial.print(" ");
  Serial.print(localTime.hour(), DEC);
  Serial.print(':');
  Serial.print(localTime.minute(), DEC);
  Serial.print(':');
  Serial.print(localTime.second(), DEC);
  Serial.println();
}

void loop() {
  // Tidak ada yang perlu dilakukan di sini, waktu sudah ditampilkan
}