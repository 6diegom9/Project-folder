#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



/*
 *        used with arduino UNO
 *        pinout:
 *        VCC   -   5V
 *        GND   -   GND
 *        CE    -   8
 *        CSN   -   10
 *        SCK   -   13
 *        MOSI  -   11
 *        MISO  -   12
 *        IRQ   -   NO CONNECTION
 * 
 */

// (CE,CSN)
RF24 radio(8,10);

const byte address[6] = "00001";


void setup() {

  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);   radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
}

void loop() {
    char text[32] = "";
  
  if (radio.available()) {
    radio.read(&text, sizeof(text));
    String transData = String(text);
    
        Serial.println(transData);
        delay(500);
  }


  const char text[] = "Diego finally made it work";
  radio.write(&text, sizeof(text));
  
  Serial.println("data sent");
  delay(100);


  
  

  


}
