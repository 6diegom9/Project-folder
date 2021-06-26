/*
 * 
 * 
 *          Brown   = GND
 *          Red     = Vcc (3.5v~6v)
 *          Orange  = Signal (PWM)
 * 
 * 
 * 
 */



 
#include <Servo.h>
Servo myservo;  // create servo object to control a servo

// Signal Pin
int Snal = 9 ; int i;


void setup() {

  myservo.attach(Snal);  // attaches the servo on Signal pin to the servo object
}

void loop() {

// Will move servo back and forth to its limits

    
    myservo.write(0);   
    delay(300);
    myservo.write(179);     
    delay(300);
  



}
