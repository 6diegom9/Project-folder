#include <HCSR04.h>

byte triggerPin = 35;
byte echoPin = 37;

float d2,d3,d4,d5,d6,d7,d8,dsum,d1_avg,tf,t0 ;
double* d1 = HCSR04.measureDistanceCm();
int i ;


void setup () {
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPin);
  // Red LED
  pinMode(52,OUTPUT);
}

void loop () {
  
  digitalWrite(52,LOW);
  t0 = millis() ; 

  // Resetting values for loop
   d1_avg = 0 ;  i = 0 ;
  // While condition integer based on desired number of collections for average
  while (i != 70){
  
  d1 = HCSR04.measureDistanceCm();
  d1_avg = d1_avg + d1[0];
  i = i + 1 ;
  
  }

  dsum =  d1_avg / 70 ;

  // Set based on desired distance
  if (0.393701*dsum < 45) {
    
    // Turns on LED if condition met
  digitalWrite(52,HIGH);
  }
  else{
    
  // LED stays off with failure to meet condition
  digitalWrite(52,LOW);
  
 
  }
  
  // cm to inch conversion
  Serial.print(0.393701*dsum);
  Serial.println(" inches ");
  
 
  tf = millis() ;
  Serial.print(tf-t0); Serial.println("ms to execute") ;
  Serial.println("---");
  delay(100);
  
}
