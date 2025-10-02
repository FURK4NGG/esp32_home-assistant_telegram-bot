#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>
#include <DHT.h>
#include <DHT_U.h>
#include "DHT.h"
#define DHTPIN 14
#define DHTTYPE DHT11
DHT meraklimuhendis(DHTPIN, DHTTYPE);
// Replace with your network credentials
const char* ssid = "";
const char* password = "";
#define BOTtoken ""  // your Bot Token (Get from Botfather)
#define CHAT_ID ""
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

int deger;
int i = 0;
int g = 0;
int ledState = 0;
int alarmm = 0;
int button = 0;
int buzzerPin = 15;
int buttonPin = 16;
const int earthqSensor = 0; // Earthquake Sensor
const int ledPin = 4; // Flash Pin
const int motionSensor = 12; // PIR Motion Sensor
const int gasSensor = 13; // Toxic Gas Sensor
const int waterSensor = 2; // Water Sensor
bool motionDetected = false;
bool gasDetected = false;
bool waterDetected = false;
bool useMotion = true;
bool useGas = true;
bool useWater = true;
bool useTemperature = true;
bool useEartq = true;
int useBuzzer = 0;//Alarm kullanildigi zaman sensorleri kullanma
int veri = 0;
int publicbuzzer = 0;//ses acma kapama
int alarmBuzzer = 0;//alarm sensorlerinde sensor ac kapat
int a = 0;
int b = 0;
int c = 0;

// Indicates when motion is detected
void IRAM_ATTR detectsMovement() {
  //Serial.println("MOTION DETECTED!!!");
  motionDetected = true;
}
void IRAM_ATTR detectsToxic() {
  //Serial.println("TOXIC GAS DETECTED!!!");
  gasDetected = true;
}
void IRAM_ATTR detectsWater() {
  //Serial.println("WATER DETECTED!!!");
  waterDetected = true;
}

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  //Serial.println("handleNewMessages");
  //Serial.println(String(numNewMessages));
  veri=0;//Gelen verinin anlaşılıp anlaşılmadığını bize iletiyor.
  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    //Serial.println(text);
    String from_name = bot.messages[i].from_name;

    if (text == "/start"){
      String start = "-Furkan KARLIOĞLU'nun HOME UYGULAMASINA HOŞ GELDİNİZ- \n";
      start += "Evinizdeki cihazınız ile etkileşime geçmek için gereken komutları '/help' ile bulabilirsiniz\n";
      start += "!Hata mesajı alıyorsanız geliştirici kişi ile iletişime geçiniz.(e-posta adresi:)!";
      bot.sendMessage(chat_id, start, "");
      text = "/help";
      }
    
    if (text == "/help") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/is_online to will you now online information\n";
      welcome += "/led_on to turn GPIO ON \n";
      welcome += "/led_off to turn GPIO OFF \n";
      welcome += "/set_alarm to set the 'HOME' alarm \n";
      welcome += "/close_alarm to turn off the 'HOME' alarm \n";
      welcome += "/temperature to get temperature and humidity \n";
      welcome += "/play_sound to open the buzzer \n";
      welcome += "/close_sound to close the buzzer \n";
      welcome += "/active_(motion,gas,water,fire,eartq,buzzer) to make active the components \n";
      welcome += "/deactive_(motion,gas,water,fire,eartq,buzzer) to make deactive the components -none buzzer value is deactive- \n";
      bot.sendMessage(chat_id, welcome, "");
      veri = 1;
    }

    if (text == "/led_on") {
      bot.sendMessage(chat_id, "LED state set to ON", "");
      ledState = 1;
      digitalWrite(ledPin, ledState);
      veri = 1;
    }
    
    if (text == "/led_off") {
      bot.sendMessage(chat_id, "LED state set to OFF", "");
      ledState = 0;
      digitalWrite(ledPin, ledState);
      veri = 1;
    }
    
    if (text == "/set_alarm") {
      bot.sendMessage(chat_id, "Alarm is set", "");
      alarmm = 1;
      veri = 1;
    }

    if (text == "/close_alarm") {
      bot.sendMessage(chat_id, "Alarm turned off", "");
      alarmm = 0;
      veri = 1;
    }

   if (text == "/temperature") {
      float h = meraklimuhendis.readHumidity();
      float t = meraklimuhendis.readTemperature();
      float f = meraklimuhendis.readTemperature(true);
      String myHum = String(h);
      String myTemp = String(t);
      String myFah = String(f);
      bot.sendMessage(chat_id,"Humidity: %"+myHum+"\n"+"Temperature: "+myTemp+"*C\n"+"Fahrenheit: "+myFah+"*F", "");
      veri = 1;
    }
    if (text == "/is_online") {bot.sendMessage(CHAT_ID, "Server is online now!", "");veri = 1;}
    if (text == "/active_motion") {useMotion=true;bot.sendMessage(CHAT_ID, "Motion sensor active", "");veri = 1;}
    if (text == "/active_gas") {useGas=true;bot.sendMessage(CHAT_ID, "Gas sensor active", "");veri = 1;}
    if (text == "/active_water") {useWater=true;bot.sendMessage(CHAT_ID, "Water sensor active", "");veri = 1;}
    if (text == "/active_fire") {useTemperature=true;bot.sendMessage(CHAT_ID, "Temperature sensor active", "");veri = 1;}
    if (text == "/active_eartq") {useEartq=true;bot.sendMessage(CHAT_ID, "Earthquake sensor active", "");veri = 1;}
    if (text == "/active_buzzer") {useBuzzer=1;bot.sendMessage(CHAT_ID, "Buzzer active", "");veri = 1;}
    if (text == "/deactive_motion") {useMotion=false;bot.sendMessage(CHAT_ID, "Motion sensor deactive", "");veri = 1;}
    if (text == "/deactive_gas") {useGas=false;bot.sendMessage(CHAT_ID, "Gas sensor deactive", "");veri = 1;}
    if (text == "/deactive_water") {useWater=false;bot.sendMessage(CHAT_ID, "Water sensor deactive", "");veri = 1;}
    if (text == "/deactive_fire") {useTemperature=false;bot.sendMessage(CHAT_ID, "Temperature sensor deactive", "");veri = 1;}
    if (text == "/deactive_eartq") {useEartq=false;bot.sendMessage(CHAT_ID, "Earthquake sensor deactive", "");veri = 1;}
    if (text == "/deactive_buzzer") {useBuzzer=0;bot.sendMessage(CHAT_ID, "Buzzer deactive", "");veri = 1;}
    if (text == "/play_sound") {publicbuzzer=1;digitalWrite(buzzerPin,HIGH);bot.sendMessage(CHAT_ID, "Sound is playing!!", "");veri = 1;}
    if (text == "/close_sound") {publicbuzzer=0;digitalWrite(buzzerPin,LOW);bot.sendMessage(CHAT_ID, "Sound is closed!", "");veri = 1;}
    if (veri == 0){bot.sendMessage(CHAT_ID, "Please enter a valid value!!", "");}
    }
}

void setup() {
  Serial.begin(115200);
  meraklimuhendis.begin();
  pinMode(buzzerPin,OUTPUT);
  pinMode(motionSensor,INPUT_PULLUP);
  pinMode(gasSensor,INPUT_PULLUP);
  pinMode(waterSensor,INPUT_PULLUP);
  pinMode(earthqSensor,INPUT);
  pinMode(buttonPin,INPUT);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
  attachInterrupt(digitalPinToInterrupt(gasSensor), detectsToxic, RISING);
  attachInterrupt(digitalPinToInterrupt(waterSensor), detectsWater, RISING);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    //Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  //Serial.println(WiFi.localIP());
  bot.sendMessage(CHAT_ID, "Bot started up", "");
}
void loop() {
  digitalWrite(buzzerPin,publicbuzzer);
  if(alarmm==1){
    button = digitalRead(buttonPin);
    deger = digitalRead(earthqSensor);
    digitalWrite(buzzerPin,alarmBuzzer);
    float t = meraklimuhendis.readTemperature();
    if(button == 0){alarmBuzzer = 0;digitalWrite(buzzerPin,LOW);bot.sendMessage(CHAT_ID, "Alarm is deactive for 30 seconds!!", "");
      delay(30000);
      bot.sendMessage(CHAT_ID, "Alarm is active!", "");}
    if(useEartq){
      if(deger == 1){}
    if(deger==0 && i < 2 && g==0){
      i=i+1;
      g=0;
      delay(0.2);
      if(i==2){g=1;}}
    if(deger==0 && i==2 && g==1){
      Serial.println("Earthquake Detected!!");
      bot.sendMessage(CHAT_ID, "Earthquake Detected!!", "");
      if(useBuzzer){
      alarmBuzzer = 1;
      digitalWrite(buzzerPin,alarmBuzzer);}
      i=0;
      g=0;}}
    if(motionDetected && useMotion){
      bot.sendMessage(CHAT_ID, "Motion detected!!", "");
      Serial.println("Motion Detected");
      if(useBuzzer == 1){alarmBuzzer = 1;digitalWrite(buzzerPin,alarmBuzzer);}
      motionDetected = false;
      }
    if(gasDetected && useGas){
      bot.sendMessage(CHAT_ID, "Toxic gas detected!!", "");
      Serial.println("Toxic gas Detected");
      if(useBuzzer){
      alarmBuzzer = 1;
      digitalWrite(buzzerPin,alarmBuzzer);}
      gasDetected = false;
    }
    if(waterDetected && useWater){
      bot.sendMessage(CHAT_ID, "Water detected!!", "");
      Serial.println("Water Detected");
      if(useBuzzer){
      alarmBuzzer = 1;
      digitalWrite(buzzerPin,alarmBuzzer);}
      waterDetected = false;
    }
    if(t>34 && useTemperature){
      bot.sendMessage(CHAT_ID, "Fire detected!!", "");
      Serial.println("Fire Detected");
      if(useBuzzer){
      alarmBuzzer = 1;
      digitalWrite(buzzerPin,alarmBuzzer);}
    }
    }
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while(numNewMessages) {
      //Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
