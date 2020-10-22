#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

#define RS 49
#define SS 53

MFRC522 rfid(SS, RS);
MFRC522::MIFARE_Key key;


String tagval;

void setup() {
  Serial.begin(115200);
  Serial.println("con1");
  digitalWrite(SS, 1);
  delay(100);
  digitalWrite(SS, 0);
  delay(100);
  SPI.begin();
  rfid.PCD_Init();
  digitalWrite(SS, 1);
}

void readrfid() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }
  for (int i = 0; i < rfid.uid.size; i++) {
    tagval = tagval + String(rfid.uid.uidByte[i], HEX); 
    rfid.PICC_HaltA(); // stop reading
  }
  if (tagval.length() >= 5) {
    if (tagval != "") {
      Serial.println(tagval);
    }
    tagval = "";
  }
}

void loop() {
  readrfid();
}