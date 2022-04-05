void setup() {
Serial.begin(9600);

  pinMode(13,OUTPUT);

}

void loop() {

if (Serial.read() == 'a'){

digitalWrite(13,HIGH) ; 

  
}
 if (Serial.read() == 'b'){

digitalWrite(13,LOW) ; 

  
}

}
