//sda -> 10
//sck -> 13
//mosi -> 11
//miso -> 12
//rst -> 19
// vcc -> 3.3v
// gnd -> gnd

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 4 //Deklarasi pin led kuning atau hijau
#define LED_R 5 //Deklarasi pin led merah
#define BUZZER 2 //deklarasi pin buzzer

MFRC522 mfrc522(SS_PIN, RST_PIN);   // membuat inisiasi MFRC522
Servo myServo; // deklarasi variabel nama servo 
 
void setup() 
{
  Serial.begin(9600);   // membuka komunikasi serial 
  SPI.begin();      // Initiate  SPI bus inisiasi spi bus
  mfrc522.PCD_Init();   // inisiasi mfrc522
  myServo.attach(3); //deklarasi piin servo
  myServo.write(0); //posisi awal servo
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  Serial.println("Masukkan kartu akses anda");
  Serial.println();

}
void loop() 
{
  // mencari kartu baru
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // memilih salah satu kartu
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Menampilkan uid tag di serial monitor
  Serial.print("UID tag :");
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
  if (content.substring(1) == "83 FE 62 27") //sesuaikan dengan uid tag dari kartu
  {
    Serial.println("Akses diterima ");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
    myServo.write(180);
    delay(5000);
    myServo.write(0);
    digitalWrite(LED_G, LOW);
  }
 
 else   {
    Serial.println(" Akses Ditolak! ");
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
  }
} 
