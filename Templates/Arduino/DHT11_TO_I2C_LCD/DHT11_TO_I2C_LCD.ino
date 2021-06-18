#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define MAXDO   3
#define MAXCS   4
#define MAXCLK  5


void setup(){
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
}

void loop(){
  int chk = thermocouple.readInternal();
  lcd.clear();
  //lcd.print("Temp = ");
  lcd.print((chk*1.8)+32);
  lcd.print(" ");
  lcd.print((char)223);
  lcd.print("F");
  lcd.setCursor(0,1);
  lcd.print(round(DHT.humidity));
  lcd.print("%");
  lcd.print(" Humid");
  delay(5000);                       // errors (ex: -999C) at < 1000 mseconds
}
