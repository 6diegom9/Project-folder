// Using teensy 4.1 

// First sensor
#define ECHOPIN1 19
#define TRIGPIN1 18
// Second sensor
#define ECHOPIN2 6
#define TRIGPIN2 5


int R_2_LED = 28 ;
int W_1_LED = 33 ;

int measured_distance ;  int measured_distance2 ; int i ; int t0 ; int tf ; 


void setup() {

  Serial.begin(9600);
  pinMode(ECHOPIN1, INPUT_PULLUP);  pinMode(ECHOPIN2, INPUT_PULLUP); // If buggy replace 'INPUT' with 'INPUT_PULLUP'
  pinMode(TRIGPIN1, OUTPUT);        pinMode(TRIGPIN2, OUTPUT); 
  digitalWrite(ECHOPIN1, HIGH);     digitalWrite(ECHOPIN2, HIGH);

  pinMode(R_2_LED,OUTPUT);
  pinMode(W_1_LED,OUTPUT);


}

void loop() {


t0 = millis(); 



  
  digitalWrite(TRIGPIN1, LOW);    
  delayMicroseconds(2);
  digitalWrite(TRIGPIN1, HIGH);   
  delayMicroseconds(15);
  digitalWrite(TRIGPIN1, LOW);    
  
  
measured_distance = pulseIn(ECHOPIN1, HIGH, 26000) / 147  ;   // distance/147 if inches. distance/58 if cm.
    
  digitalWrite(TRIGPIN2, LOW);    
  delayMicroseconds(2);
  digitalWrite(TRIGPIN2, HIGH);   
  delayMicroseconds(15);
  digitalWrite(TRIGPIN2, LOW);    

measured_distance2 = pulseIn(ECHOPIN2, HIGH, 26000) / 147 ;   // distance/147 if inches. distance/58 if cm.





// scenarios 
if (measured_distance > 0 &&  measured_distance2 > 0){
  digitalWrite(W_1_LED,HIGH); // sensor 1
  digitalWrite(R_2_LED,HIGH); // sensor 2
 Serial.print(" Sensor 1 Triggered = "); Serial.println(measured_distance) ; Serial.print(" Sensor 2 Triggered = "); Serial.println(measured_distance2);
  tf = millis(); 
  Serial.print(tf-t0); Serial.println(" ms") ;
  Serial.println("----"); 
  delay(1000) ; 
}
if (measured_distance > 0 &&  measured_distance2 == 0){
  digitalWrite(W_1_LED,HIGH); // sensor 1
  digitalWrite(R_2_LED,LOW); // sensor 2
  Serial.print(" Sensor 1 Triggered= "); Serial.println(measured_distance) ; Serial.print(" Sensor 2 = "); Serial.println(measured_distance2);
  tf = millis(); 
  Serial.print(tf-t0); Serial.println(" ms") ;
  Serial.println("----"); 
  delay(1000) ; 
  
}
if (measured_distance == 0 &&  measured_distance2 > 0){
  digitalWrite(W_1_LED,LOW); // sensor 1
  digitalWrite(R_2_LED,HIGH); // sensor 2
  Serial.print(" Sensor 1 = "); Serial.println(measured_distance) ; Serial.print(" Sensor 2 Triggered= "); Serial.println(measured_distance2);
  tf = millis();
  Serial.print(tf-t0); Serial.println(" ms") ;
  Serial.println("----");  
  delay(1000) ; 
}
if (measured_distance == 0 && measured_distance2 == 0){
  digitalWrite(W_1_LED,LOW); // sensor 1
  digitalWrite(R_2_LED,LOW); // sensor 2
  Serial.print(" Sensor 1 = "); Serial.println(measured_distance) ; Serial.print(" Sensor 2 = "); Serial.println(measured_distance2);
  tf = millis(); 
  Serial.print(tf-t0); Serial.println(" ms") ;
  Serial.println("----"); 
}
  








 




  

}
