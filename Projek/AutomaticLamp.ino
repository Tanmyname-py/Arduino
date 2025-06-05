/*                                   *****************************************************************************
Program kontrol lampu dengan bot telegram 
Sesuaikan WIFI SSID dan PASWORD dengan wifi anda 
Ambil bot token di BotFather 
Created by @Tan
Source https://github.com/Tanmyname-py/Arduino/tree/main/Projek
*****************************************************************************
Relay -> ESP8266
Gnd   -> G
Vcc   -> 3v3
In    -> D1 GPIO 5
*****************************************************************************
*/
#include "ESP8266WiFi.h"
#include "WiFiClientSecure.h"
#include "UniversalTelegramBot.h"
#define Relay 5
#define WIFI_SSID ""
#define WIFI_PASSWORD  ""
#define BOT_TOKEN  ""
const unsigned long BOT_MTBS = 1000; // mean time between scan messages

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;

void handleMessage(int numNewMessages){
  for (int i = 0; i < numNewMessages; i++)
  {
    
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    Serial.println("----------------------------------------------");
    Serial.println("chat from => "+from_name+" message => "+text);
    Serial.println("----------------------------------------------");
    if (bot.messages[i].type == "callback_query") {
      String data = bot.messages[i].text;
      if (data == "ON") {
        digitalWrite(Relay, HIGH);  // Relay aktif
        bot.sendMessage(chat_id, "Lampu ON ✅", "");
      } else if (data == "OFF") {
        digitalWrite(Relay, LOW); // Relay mati
        bot.sendMessage(chat_id, "Lampu OFF ❌", "");
      }
    } else {
       if (text == "/start") {
        String welcome = "Halo! Ini kontrol lampu via Telegram.\nGunakan tombol di bawah untuk ON/OFF:";
        String keyboardJson = "[[{\"text\":\"💡 ON\",\"callback_data\":\"ON\"},{\"text\":\"🛑 OFF\",\"callback_data\":\"OFF\"}]]";
        bot.sendMessageWithInlineKeyboard(chat_id, welcome, "", keyboardJson);
      } else if(text == "/cek lamp"){
        int value = digitalRead(Relay);
        if (value == 1){
           String info = "Lampu dalam keadaan menyala,Ingin mematikannya? ";
           String keyboardJson = "[[{\"text\":\"🛑 OFF\",\"callback_data\":\"OFF\"}]]";
           bot.sendMessageWithInlineKeyboard(chat_id, info, "", keyboardJson);
        } else {
           String info = "Lampu dalam keadaan mati,Ingin menyalakannya? ";
           String keyboardJson = "[[{\"text\":\"💡 ON\",\"callback_data\":\"ON\"}]]";
           bot.sendMessageWithInlineKeyboard(chat_id, info, "", keyboardJson);
        }
      } else if(text == "/on"){
        digitalWrite(Relay,HIGH);
        bot.sendMessage(chat_id,"LAMPU ON ✅");
      } else if(text == "/of"){
        digitalWrite(Relay,LOW);
        bot.sendMessage(chat_id,"LAMPU OF ❌");
      } else {
        bot.sendMessage(chat_id,"Perintah tidak di ketahui ? ketik /start untuk tombol on,of. /on untuk menyalakan lampu,/of untuk mematikan lampu,dan /cek lamp untuk mengecek keadaan lampu ");
      }
    }

}}
void setup(){
  Serial.begin(115200);
  pinMode(Relay,OUTPUT);
  digitalWrite(Relay,LOW);
  Serial.println();
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);



}
void loop(){
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleMessage(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
  }
