#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 4
#define LED1_PIN 15 //rouge
#define LED2_PIN 2 //vert

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 20, 4);
const char* serverName = "https://ulkcontrolservice.vercel.app/check_rfid/";


void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  lcd.init();
  lcd.backlight();

  //WiFi.begin("UPI", "poly#2023");
 WiFi.begin("CANALBOX-3013-2G", "QqBASw5Z35");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.setCursor(0, 0);
    lcd.print("ULK -- POLYTECHNIC");
    lcd.setCursor(0, 2);
    lcd.print("Initialization...");
    lcd.setCursor(4, 3);
    lcd.print("Connecting...");
  }
  Serial.println("Connected to WiFi");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ULK -- POLYTECHNIC");
  lcd.setCursor(0, 1);
  lcd.print("Approach your card !");
  lcd.setCursor(4, 3);
  lcd.print("WiFi connected!");

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  String cardId = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    cardId += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    cardId += String(rfid.uid.uidByte[i], HEX);
  }
  cardId.toUpperCase();

  Serial.println(cardId);

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    HTTPClient http;
    client.setInsecure();  // Disable SSL certificate verification (not recommended for production)
    // client.setFingerprint("xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx"); // Example of setting fingerprint

    Serial.println("Sending HTTPS request...");

    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String postData = "cardId=" + cardId;

    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);

      DynamicJsonDocument doc(1024);
      deserializeJson(doc, response);

      const char* statuse = doc["status"];
      const char* message = doc["message"];
      //const char* nom = doc["student_name"];
      String name = String(doc["student_name"]);
      const char* roll_number = doc["roll_number"];


      name.toUpperCase();
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(name);
      lcd.setCursor(0, 1);
      lcd.print(statuse);
      lcd.setCursor(0, 2);
      lcd.print(roll_number);
      lcd.setCursor(4, 3);
      lcd.print("WiFi connected!");

       if (strcmp(statuse, "Authorized") == 0) {
        digitalWrite(LED2_PIN, HIGH);
        delay(3000);
        digitalWrite(LED2_PIN, LOW);
      } else {
        digitalWrite(LED1_PIN, HIGH);
        delay(3000);
        digitalWrite(LED1_PIN, LOW);
      }
      
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ULK -- POLYTECHNIC");
      lcd.setCursor(0, 1);
      lcd.print("Approach your card !");
      lcd.setCursor(4, 3);
      lcd.print("Wifi connected!");

     
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ERROR -- ERROR");
      lcd.setCursor(0, 2);
      lcd.print("Fail to reach server");
      digitalWrite(LED1_PIN, HIGH);
      delay(1000);
      digitalWrite(LED1_PIN, LOW);
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ULK -- POLYTECHNIC");
      lcd.setCursor(0, 1);
      lcd.print("Approach your card !");
      lcd.setCursor(4, 3);
      lcd.print("Wifi connected!");
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ULK -- POLYTECHNIC");
    lcd.setCursor(0, 1);
    lcd.print("ERROR");
    lcd.setCursor(4, 4);
    lcd.print("Connection lost!");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ULK -- POLYTECHNIC");
    lcd.setCursor(0, 2);
    lcd.print("Initialization...");
    lcd.setCursor(4, 3);
    lcd.print("Connecting...");
  }

  delay(3000);
}