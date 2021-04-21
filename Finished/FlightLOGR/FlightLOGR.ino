
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>



Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();


long t0 ; 
long tf ;
long tdiff ; 
long tc ; 


const int chipSelect = 4;
File flightlog ;


void setup() {
  Wire.setClock(1000000) ; 
  Serial.begin(9600);
 
    Serial.print("Initializing SD card...");
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  //pinMode(8,OUTPUT) ;
  pinMode(13,OUTPUT) ;
  
  SD.begin(chipSelect) ; 
}

void loop() {
  
  if (! baro.begin()) {
    Serial.println("Couldnt find sensor");
    return;
  }
   
  float pascals = baro.getPressure();
  // Our weather page presents pressure in Inches (Hg)
  // Use http://www.onlineconversion.com/pressure.htm for other units



  
flightlog = SD.open("flyLOGR.txt",FILE_WRITE);


// #13 and #8 board led flash with absent SD card
//digitalWrite(8,HIGH);
digitalWrite(13,LOW);
delay(100) ;
//digitalWrite(8,LOW);
digitalWrite(13,HIGH);


tc = millis() ;
if (flightlog){
  // #13 LED establishes data being written
  digitalWrite(13,HIGH);

  t0 =  millis();
  float altm = baro.getAltitude();
 Serial.print(pascals/3377); Serial.println(" Inches (Hg)");
 Serial.print(altm); Serial.println(" meters");

  float tempC = baro.getTemperature();
 Serial.print(tempC); Serial.println("*C");
  tf = millis() ; 
  tdiff = tf - t0 ;

  //Time(s) | Inches (Hg) | Altitude (meters) | Temperature (C) | Execute time
  Serial.print(tdiff); Serial.println(" ms to execute");
 Serial.print(tc*.001) ;  Serial.println(" s run time");
 //delay(250);

flightlog.print(tc*.001); flightlog.print(" , "); flightlog.print(pascals/3377);flightlog.print(" , ");flightlog.print(altm);flightlog.print(" , ");flightlog.print(tempC);flightlog.print(" , ");flightlog.println(tdiff);



}
flightlog.close();
}
