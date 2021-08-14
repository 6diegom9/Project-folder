/* Using teensy 4.1 

  This code filters data and requires 2/6 samples to trigger desired measurement distance at around 300ms.
  
  This is NOT needed as street driving tests showed cars can pass by at only trigger 1-2 out of 6 samples in high speed settings. For lower speed, this would be ideal.
  Test run showed low possibility of false triggers. Sensors gave a 0 reading for ALL of the time until a car passed.
  This code works best in analyzing sensor capturing capability through a longer period of time. Not recommended for regular driving trigger for notifying driver.












*/

// First sensor
#define ECHOPIN1 19
#define TRIGPIN1 18
// Second sensor
#define ECHOPIN2 6
#define TRIGPIN2 5


int R_2_LED = 28 ;
int W_1_LED = 33 ;

int measured_distance[6] ;  int measured_distance2[6] ; int i ; int j; int t0 ; int tf ; int i1 ; int i2;


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

// Taking 6 "i < 6" readings one after another
i = 0 ;
 while (i < 6){
  
  digitalWrite(TRIGPIN1, LOW);    
  delayMicroseconds(2);
  digitalWrite(TRIGPIN1, HIGH);   
  delayMicroseconds(15);
  digitalWrite(TRIGPIN1, LOW);    
  
  
measured_distance[i] = pulseIn(ECHOPIN1, HIGH, 26000) / 147  ;   // distance/147 if inches. distance/58 if cm.
    
  digitalWrite(TRIGPIN2, LOW);    
  delayMicroseconds(2);
  digitalWrite(TRIGPIN2, HIGH);   
  delayMicroseconds(15);
  digitalWrite(TRIGPIN2, LOW);    

measured_distance2[i] = pulseIn(ECHOPIN2, HIGH, 26000) / 147 ;   // distance/147 if inches. distance/58 if cm.

 i = i + 1 ; 


 }






// Counting the amount of the 6 samples falling between desired distance
// i1,i2 represent the amount of samples which triggered per sensor
i = 0 ; i1 = 0; i2 = 0;
while (i < 6){

if (measured_distance[i] < 42 && measured_distance[i] != 0 ){
  i1 = i1 + 1 ; 
}
if (measured_distance2[i] < 42 && measured_distance2[i] != 0){
  i2 = i2 + 1 ; 
}

i = i + 1 ;
} 

// Printing 6 readings per sensor
Serial.println("Sensor 1");
Serial.print(measured_distance[0]); Serial.print(" "); Serial.print(measured_distance[1]); Serial.print(" "); Serial.print(measured_distance[2]); Serial.print(" "); Serial.print(measured_distance[3]); Serial.print(" "); Serial.print(measured_distance[4]); Serial.print(" "); Serial.println(measured_distance[5]); 
Serial.println("Sensor 2");
Serial.print(measured_distance2[0]); Serial.print(" "); Serial.print(measured_distance2[1]); Serial.print(" "); Serial.print(measured_distance2[2]); Serial.print(" "); Serial.print(measured_distance2[3]); Serial.print(" "); Serial.print(measured_distance2[4]); Serial.print(" "); Serial.println(measured_distance2[5]); 


// scenarios 
if (i1 >= 3 && i2 >= 3){
  digitalWrite(W_1_LED,HIGH); // sensor 1
  digitalWrite(R_2_LED,HIGH); // sensor 2
}
if (i1 >= 3 && i2 < 3){
  digitalWrite(W_1_LED,HIGH); // sensor 1
  digitalWrite(R_2_LED,LOW); // sensor 2
}
if (i1 < 3 && i2 >= 3){
  digitalWrite(W_1_LED,LOW); // sensor 1
  digitalWrite(R_2_LED,HIGH); // sensor 2
}
if (i1 < 3 && i2 < 3){
  digitalWrite(W_1_LED,LOW); // sensor 1
  digitalWrite(R_2_LED,LOW); // sensor 2
}
  







  tf = millis(); 
  Serial.print("i1 = "); Serial.println(i1);
  Serial.print("i2 = "); Serial.println(i2);  
 
  Serial.print(tf-t0); Serial.println(" ms") ;
  Serial.println("----"); 



  

}
