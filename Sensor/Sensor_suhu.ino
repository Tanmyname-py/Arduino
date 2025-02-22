#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define Lebar_Screen 128
#define Tinggi_Screen 64

// Inisialisasi display SSD1306
Adafruit_SSD1306 display(Lebar_Screen, Tinggi_Screen, &Wire, -1);

#define DHT_PIN D5  // Pin untuk sensor DHT (D5 untuk ESP8266)
DHT dht(DHT_PIN, DHT11); // Menggunakan sensor DHT11

float t, h;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  // Inisialisasi layar OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay(); // Bersihkan layar OLED
  
  // Tampilkan pesan awal pada OLED
  display.setTextSize(1);      
  display.setTextColor(WHITE);  
  display.setCursor(0, 0);     
  display.println(F("Suhu dan Kelembaban"));
  display.display();
  delay(2000);  // Tunggu 2 detik
}

void loop() {
  // Membaca suhu dan kelembaban dari sensor DHT11
  t = dht.readTemperature();  // Baca suhu
  h = dht.readHumidity();     // Baca kelembaban
  
  // Periksa apakah pembacaan gagal
  if (isnan(t) || isnan(h)) {
    Serial.println(F("Tidak dapat membaca sensor DHT11"));
    return;
  }

  // Kirim data ke Serial Monitor
  Serial.println("TEMP: " + String(t) + " ℃");
  Serial.println("Humd: " + String(h) + " %");
  
  // Tampilkan data suhu dan kelembaban di layar OLED
  display.clearDisplay();  // Bersihkan layar sebelum menampilkan data baru
  display.setCursor(0, 28);
  display.setTextSize(1);
  display.print(F("TEMP: "));
  display.print(t);
  display.print(char(223));  // Menampilkan simbol derajat Celsius
  display.println(F(" C"));
  
  display.print(F("HUMD: "));
  display.print(h);
  display.println(F(" %"));
  
  display.display();  // Update layar OLED dengan data baru
  
  delay(1000);  // Delay 1 detik sebelum membaca lagi
}
