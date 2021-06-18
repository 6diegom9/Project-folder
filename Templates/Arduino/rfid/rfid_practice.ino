/*

PINOUT for
     UNO                              
RST  -  9 (PWM)                  
MISO - 12                         
MOSI - 11 (PWM)                   
SCK  - 13                         
SDA  - 10 (PWM)                   




*/
#include <SPI.h>
#include <MFRC522.h>

 
#define SS_PIN 10
#define RST_PIN 9


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  
  //Show UID on serial monitor
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
  Serial.print("Message : ");
  content.toUpperCase();
  
  // For tag
  if (content.substring(1) == "07 64 3F B4") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access with tag");
    digitalWrite(13,HIGH);
  }


  // For Card
  if (content.substring(1) == "80 5A 9C 93") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access with Card");
    digitalWrite(13,HIGH);
  }

 
delay(5000);
} 
