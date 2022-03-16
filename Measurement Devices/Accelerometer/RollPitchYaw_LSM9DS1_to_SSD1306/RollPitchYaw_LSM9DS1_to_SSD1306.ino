#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h> 
#include <ACROBOTIC_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C 
#define LSM9DS1_SCK A5
#define LSM9DS1_MISO 12
#define LSM9DS1_MOSI A4
#define LSM9DS1_XGCS 6
#define LSM9DS1_MCS 5
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int roll; int pitch; int yaw; int acc_magnitude; 
unsigned long t0; unsigned long tf;


// I2C
//TEENSY  pin 19 for SCL. 18 for SDA.
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();






void setupSensor()
{

  pinMode(13,OUTPUT);
  // Accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);
  

}


void setup() 
{
 Serial.begin(115200);

  Serial.println("LSM9DS1 data read demo");
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF");
  
  setupSensor();

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  delay(2000); 



}

void loop() 
{

  t0 = millis();
  digitalWrite(13,HIGH);
      display.display(); display.clearDisplay();
  
  
 
  lsm.read();  sensors_event_t a, m, g, temp; lsm.getEvent(&a, &m, &g, &temp); 

 
  pitch = (180/M_PI) * atan (a.acceleration.x/sqrt(a.acceleration.y*a.acceleration.y + a.acceleration.z*a.acceleration.z));
  roll = (180/M_PI) * atan (a.acceleration.y/sqrt(a.acceleration.x*a.acceleration.x + a.acceleration.z*a.acceleration.z));
  yaw = (180/M_PI) * atan (sqrt(a.acceleration.x*a.acceleration.x + a.acceleration.z*a.acceleration.z)/a.acceleration.z);


  
  
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(5,5);             // Start at top-left corner
  display.print("Roll: "); 
  display.print(roll);
  display.print((char)247);
  display.setCursor(5,20); 
  display.print("Pitch:"); 
  display.print(pitch);
  display.print((char)247);
  display.setCursor(5,35); 
  display.print("Yaw:  "); 
  display.print(yaw);
  display.print((char)247);
  tf = millis();
  display.setCursor(5,50); 
  display.print("  ");
  display.print(tf-t0);
  display.print(" ms");

  
  delay(100);
}
