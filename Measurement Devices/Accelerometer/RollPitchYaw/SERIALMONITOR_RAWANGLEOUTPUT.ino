#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h> 
#include <ACROBOTIC_SSD1306.h>




signed long roll; int pitch; int yaw; int acc_magnitude; int roll2; int pitch2; int yaw2;

// I2C
//TEENSY  pin 19 for SCL. 18 for SDA.
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

#define LSM9DS1_SCK A5
#define LSM9DS1_MISO 12
#define LSM9DS1_MOSI A4
#define LSM9DS1_XGCS 6
#define LSM9DS1_MCS 5




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
    delay(1); 
  }
  Serial.println("LSM9DS1 data read demo");
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF");
  setupSensor();



}

void loop() 
{
  lsm.read(); 


  sensors_event_t a, m, g, temp;

  lsm.getEvent(&a, &m, &g, &temp); 

 
  pitch = (180/M_PI) * atan (a.acceleration.x/sqrt(a.acceleration.y*a.acceleration.y + a.acceleration.z*a.acceleration.z));
  roll = (180/M_PI) * atan (a.acceleration.y/sqrt(a.acceleration.x*a.acceleration.x + a.acceleration.z*a.acceleration.z));
  yaw = (180/M_PI) * atan (sqrt(a.acceleration.x*a.acceleration.x + a.acceleration.z*a.acceleration.z)/a.acceleration.z);






  delay(100);
}
