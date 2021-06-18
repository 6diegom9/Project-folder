
// Uno pinout
const int sw = 4  ; // digital 4 
const int VRx = 0 ; // A0 Pin
const int VRy = 1 ; // A1 Pin




void setup() {

Serial.begin(9600);
pinMode(sw,INPUT); 
digitalWrite(sw,HIGH); 
  

}

void loop() {


/*              RANGE 
 *          NEG MAX - MID - POS MAX
 *           
 *           
 *          Rx:   0 -  520 - 1023   LEFT TO RIGHT
 *          Ry:   0 -  505 - 1023   UP TO DOWN
 * 
 *          SW: 0 = Pressed
 *              1 = Not pressed
 * 
 * 
 */
Serial.print("switch: ") ; Serial.println(digitalRead(sw));
Serial.print("Rx: ") ; Serial.println(analogRead(0));
Serial.print("Ry: ") ; Serial.println(analogRead(1));


delay(600);






  

}
