
#include <ArducamSSD1306.h>   
#include <Adafruit_GFX.h>   
#include <Wire.h>           
#include <SPI.h>
#include "Adafruit_MAX31855.h"



#define MAXDO   11 // PWM
#define MAXCS   6
#define MAXCLK  10 // PWM
#define OLED_RESET  7 // Not required to connect

// initialize Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);
ArducamSSD1306 display(OLED_RESET);

// Variable Initialization
float tempff ;
String stempff; 

void setup() {
  
  //Serial.begin(115200);
  display.begin();
 
}

void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20,25);

  // Temp display
  tempff = thermocouple.readFahrenheit() ;
  stempff = String(tempff) ;
  display.print(stempff); display.print(" F ");
 
  display.display();

   delay(500);
}
