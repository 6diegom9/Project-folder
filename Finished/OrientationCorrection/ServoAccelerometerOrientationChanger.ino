#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  
#include <Servo.h>

Servo servo;

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
float t0,tf,roll,pitch,acc_magnitude,a1x_avg,a1y_avg,a1z_avg,a1x,a1y,a1z,ax,ay,az,servoroll ;
int i ; 


void setupSensor()
{
  // Accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);

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

  // Servo pin decleration
  servo.attach(9);
  
}

void loop() 
{
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
ax = a1x_avg / 10  ; ay = a1y_avg / 10 ; az = a1z_avg / 10 ; 


  Serial.print("Accel X: "); Serial.print(ax); Serial.print(" m/s^2");          // Calibrate by adding based on surface conditions
  Serial.print("\tY: "); Serial.print(ay);     Serial.print(" m/s^2 ");         // Calibrate by adding based on surface conditions
  Serial.print("\tZ: "); Serial.print(az);     Serial.println(" m/s^2 ");           // Calibrate by adding based on surface conditions

  // Default is radians. 180/PI = 57.29577951
  acc_magnitude = sqrt((ax*ax)+(ay*ay)+(az*az)); 
  roll = asin((float)ax/acc_magnitude)* -57.29577951;  
  pitch = asin((float)ay/acc_magnitude)* 57.29577951;



  // 8 - 168 is the non vibrating range for my personal servo 
  // 3 degree roll is initial position degree on my table
  servoroll = map(roll, -90,90,8,168);
  servo.write(servoroll);





  Serial.print(roll);     Serial.println(" roll angle ");
  Serial.print(pitch);     Serial.println(" pitch angle ");
  tf = millis();
  // Execute time
  Serial.print(tf-t0);     Serial.println(" ms "); 

  

  Serial.println();
 
}
