/*
WIRING: 
Using Uno,

vcc - 5 V
GND - GND
OUT - 4 (digital I/O)



Pinout for nonboard receiver (NO RESISTOR NEEDED!)
            faceup
   |         |             |
  PIN       GND            5V


  Sender NEEDS resistor

*/
#include <IRremote.h> //include the library



int receiver = 4; //initialize pin 4 as recevier pin.
IRrecv irrecv(receiver); //create a new instance of receiver
decode_results results;


void setup() {
 Serial.begin(9600);
 irrecv.enableIRIn(); //start the receiver

}
void loop() {
 if (irrecv.decode(&results)) { //if we have received an IR signal
 Serial.println(results.value, HEX); //display HEX results 
 irrecv.resume(); //next value
 }

 }
 
