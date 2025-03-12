//sda -> 10
//sck -> 13
//mosi -> 11
//miso -> 12
//rst -> 9
// vcc -> 3.3v//sda -> 10
//sck -> 13
//mosi -> 11
//miso -> 12
//rst -> 9
// vcc -> 3.3v
// gnd -> gnd
// gnd -> gnd
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#define Lebar_Screen 128
#define Tinggi_Screen 64
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 4 //Deklarasi pin led kuning atau hijau
#define LED_R 5 //Deklarasi pin led merah
#define BUZZER 3 //deklarasi pin buzzer
Adafruit_SSD1306 display(Lebar_Screen,Tinggi_Screen,&Wire,-1);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // membuat inisiasi MFRC522
Servo myservo;
void setup() 
{
  display.begin(SSD1306_SWITCHCAPVCC,0x3c);
  myservo.attach(6);
  delay(2000);
  display.clearDisplay();
  Serial.begin(9600);   // membuka komunikasi serial 
  SPI.begin();      // Initiate  SPI bus inisiasi spi bus
  mfrc522.PCD_Init();   // inisiasi mfrc522
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,28);
  display.println("Scan kartu anda ");
  display.display();
  display.clearDisplay();
  Serial.println("Masukkan kartu akses anda");
  Serial.println();

}
void loop() 
{
  myservo.write(0);
  noTone(BUZZER);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,28);
  display.println("Scan kartu anda ");
  display.display();
  display.clearDisplay();
  digitalWrite(LED_G,LOW);
  digitalWrite(LED_R, LOW);
  if ( ! mfrc522.PICC_IsNewCardPresent())   // mencari kartu baru
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())   // memilih salah satu kartu
  {
    return;
  }
  Serial.print("UID tag :");   //Menampilkan uid tag di serial monitor
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Pesan : ");
  content.toUpperCase();
  if (content.substring(1) == "A3 35 87 28") //sesuaikan dengan uid tag dari kartu
  {
    myservo.write(90);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20,28);
    display.println("Akses diterima ");
    display.display();
    display.clearDisplay();
    Serial.println("Akses diterima ");
    Serial.println();
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(300);
    digitalWrite(LED_G, LOW);
    noTone(BUZZER);
    delay(1000);
  }
 else {
    myservo.write(0);
    digitalWrite(LED_R,HIGH);
    tone(BUZZER,1000);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20,28);
    display.println("Akses Ditolak! ");
    display.display();
    display.clearDisplay();
    Serial.println(" Akses Ditolak! ");
    delay(1000);
 }
}
