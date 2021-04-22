
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();


long t0 ; 
long tf ;
long tdiff ; 
long tc ; 


const int chipSelect = BUILTIN_SDCARD;
File flightlog ;


void setup() {
  
 
    Serial.print("Initializing SD card...");
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    digitalWrite(13,LOW);
    delay(100) ;
    digitalWrite(13,HIGH);
     delay(100) ;
    // don't do anything more:
    return;
  }
  
  pinMode(13,OUTPUT) ;
  
  SD.begin(chipSelect) ; 
}

void loop() {
  

  float pascals = baro.getPressure();



  
flightlog = SD.open("flyLOGR.txt",FILE_WRITE);


// #13 board led flash with absent SD card


tc = millis() ;
if (flightlog){
  // #13 LED establishes data being written
  digitalWrite(13,HIGH);

  t0 =  millis();
  float altm = baro.getAltitude();


  float tempC = baro.getTemperature();

  tf = millis() ; 
  tdiff = tf - t0 ;

  // Time(s) | Inches (Hg) | Altitude (meters) | Temperature (C) | Execute time
flightlog.print(tc*.001); flightlog.print(" , "); flightlog.print(pascals/3377);flightlog.print(" , ");flightlog.print(altm);flightlog.print(" , ");flightlog.print(tempC);flightlog.print(" , ");flightlog.println(tdiff);
flightlog.close();


}
}
