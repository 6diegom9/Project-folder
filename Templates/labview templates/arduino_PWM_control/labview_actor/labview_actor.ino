int x ; String xstr ; 
void setup() {
Serial.begin(9600);

  pinMode(2,OUTPUT);
  pinMode(13,OUTPUT) ;

}

void loop() {




while (Serial.available() != 0){
  digitalWrite(13,HIGH) ; 
xstr = Serial.read() ;
analogWrite(2,xstr.toInt()) ;





}

}
