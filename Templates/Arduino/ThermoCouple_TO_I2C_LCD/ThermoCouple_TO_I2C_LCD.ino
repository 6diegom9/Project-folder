/***************************************************
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MAX31855.h"
#include <LiquidCrystal_I2C.h>

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define MAXDO   48
#define MAXCS   50
#define MAXCLK  52

// Initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.print("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(5000);
  if (!thermocouple.begin()) {
    lcd.print("ERROR.");
    while (1) delay(10);
  }
  lcd.print("DONE.");
}

void loop() {
  // basic readout test, just print the current temp
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Int. Temp = ");
   lcd.println(thermocouple.readInternal());
  
   double F = thermocouple.readFahrenheit();
   lcd.setCursor(0, 1);
   if (isnan(F))
   {
     lcd.print("T/C Problem");
   }
   else
   {
     lcd.print("Temp = ");
     lcd.print(F);
     lcd.print(" ");
     lcd.print((char)223);
     lcd.print("F");
     
   }

   delay(1000);
}
