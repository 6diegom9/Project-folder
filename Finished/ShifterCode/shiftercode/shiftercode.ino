#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  


// i2c connection
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

// Not used with teensy 
// pin 19 for SCL. 18 for SDA
#define LSM9DS1_SCK A5
#define LSM9DS1_MISO 12
#define LSM9DS1_MOSI A4
#define LSM9DS1_XGCS 6
#define LSM9DS1_MCS 5

// variables
float t0,tf,roll,pitch,acc_magnitude,a1x_avg,a1y_avg,a1z_avg,a1x,a1y,a1z,ax,ay,az,pinswitch,debugLED, roll_init,pitch_init, roll_diff, pitch_diff ;
int i,f,d,p,z,t1,t2 ; 



void setupSensor()
{
  debugLED = 13;
  // Accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);

  // Debug LED to confirm code reaches loop
  pinMode(debugLED,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(24,OUTPUT);
  z = 0 ;
}


void setup() 
{
  Serial.begin(115200);

  while (!Serial) {
    delay(1); // will pause Zero, Leonardo, etc until serial console opens
  }
  
  Serial.println("LSM9DS1 data read demo");
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Check wiring...");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF");
  
  // sensor begin
  setupSensor();
  lsm.read();  
  
  f = 0 ;
  d = 0 ;
  z = 0 ;
}

void loop(){

// Used to take note of car orientation (uphill, downhill, etc.) in neutral shift gear state
while (d == 0) {

t0 = millis();  

   // Resetting integers
   a1x_avg = 0 ; a1y_avg = 0 ; a1z_avg = 0 ; i = 0 ;

   
  // While condition integer based on desired number of collections for average
  while (i != 10){
  sensors_event_t a, m, g, temp;
  lsm.getEvent(&a, &m, &g, &temp); 
  a1x = a.acceleration.x ;
  a1y = a.acceleration.y ;
  a1z = a.acceleration.z ;

  a1x_avg = a1x_avg + a1x ;
  a1y_avg = a1y_avg + a1y ;
  a1z_avg = a1z_avg + a1z ;

  
  i = i + 1 ;
  }

// Calculating averages. Division dependent on while loop condition
ax= a1x_avg / 10  ; ay = a1y_avg / 10 ; az = a1z_avg / 10 ; 



  Serial.print("Accel X: "); Serial.print(ax); Serial.print(" m/s^2");          // Calibrate by adding based on surface conditions
  Serial.print("\tY: "); Serial.print(ay);     Serial.print(" m/s^2 ");         // Calibrate by adding based on surface conditions
  Serial.print("\tZ: "); Serial.print(az);     Serial.println(" m/s^2 ");           // Calibrate by adding based on surface conditions

  // Default is radians. 180/PI = 57.29577951
  acc_magnitude = sqrt((ax*ax)+(ay*ay)+(az*az)); 
  roll_init = asin((float)ax/acc_magnitude)* -57.29577951;  
  pitch_init = asin((float)ay/acc_magnitude)* 57.29577951;

d = 1;
}


 
  
  while (p == 0) {
   
   a1x_avg = 0 ; a1y_avg = 0 ; a1z_avg = 0 ; i = 0 ;

   
  // While condition integer based on desired number of collections for average
  while (i != 10){
  sensors_event_t a, m, g, temp;
  lsm.getEvent(&a, &m, &g, &temp); 
  a1x = a.acceleration.x ;
  a1y = a.acceleration.y ;
  a1z = a.acceleration.z ;

  a1x_avg = a1x_avg + a1x ;
  a1y_avg = a1y_avg + a1y ;
  a1z_avg = a1z_avg + a1z ;

  
  i = i + 1 ;
  }

// Calculating averages. Division dependent on while loop condition
ax= a1x_avg / 10  ; ay = a1y_avg / 10 ; az = a1z_avg / 10 ; 



  //Serial.print("Accel X: "); Serial.print(ax); Serial.print(" m/s^2");          // Calibrate by adding based on surface conditions
  //Serial.print("\tY: "); Serial.print(ay);     Serial.print(" m/s^2 ");         // Calibrate by adding based on surface conditions
  //Serial.print("\tZ: "); Serial.print(az);     Serial.println(" m/s^2 ");           // Calibrate by adding based on surface conditions

  // Default is radians. 180/PI = 57.29577951
  acc_magnitude = sqrt((ax*ax)+(ay*ay)+(az*az)); 
  roll = asin((float)ax/acc_magnitude)* -57.29577951;  
  pitch = asin((float)ay/acc_magnitude)* 57.29577951;

 // roll and pitch adjusted to auto configure values in the beginning which compensate uphill parking etc.
 roll_diff = abs(roll_init)-abs(roll) ;
 pitch_diff = abs(pitch_init)-abs(pitch) ; 
 
 Serial.print("roll diff: "); Serial.println(roll_diff) ; 
 Serial.print("pitch diff: "); Serial.println(pitch_diff) ; 

  // Taking note if shifter hits 3rd gear and time from first completion to final action
  if ( z == 0 && roll_diff < -43 && pitch_diff > 40 ){
  digitalWrite(24,LOW);
  digitalWrite(26,HIGH);
  p = 0; f = f + 1 ;t1 = .001*(millis()); delay(500);
  }
  
  if (f == 3){
  p = 1 ;
  digitalWrite(24,HIGH);
  digitalWrite(26,HIGH);
  digitalWrite(debugLED,HIGH);
  }
 
 // status checking if it hits 3rd gear 
 // t1 will be further configured to add for restart of entire process within 3 seconds etc.
 Serial.println(t1);
 Serial.println(f);

  }

  // Visual representation of Mosfet allowing current until the car is turned off, turning off the arduino.
  digitalWrite(24,HIGH);
  delay(10);
  digitalWrite(26,HIGH);
  delay(10);
  digitalWrite(debugLED,HIGH);
  delay(10);
  digitalWrite(24,LOW);
  delay(10);
  digitalWrite(26,LOW);
  delay(10);
  digitalWrite(debugLED,LOW);
  delay(10);


}
