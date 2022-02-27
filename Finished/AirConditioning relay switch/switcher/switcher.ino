




int switchpin = 3 ;        // Relay Pin
unsigned long OnTime = 1 * 60000;    // ( On time in minutes ) 
unsigned long OffTime = 15  * 60000 ;    //( On time in minutes )

// ms output after * 6000 


void setup() {


pinMode(switchpin,OUTPUT);


}

void loop() {

digitalWrite(switchpin,HIGH) ;

delay(OnTime);

digitalWrite(switchpin,LOW);

delay(OffTime);

}
