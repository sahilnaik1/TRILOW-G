

#include "oldmotors.h"

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  pinMode(14, OUTPUT); //MOSFET to turn on/off 24V channel

  initializeRP();
  initializeTED();

}
float starttime = millis();
bool notcompleted = true;
float endtime = 500 * 1000;
bool notcompleted2 = true;
float endtime2 = 500 * 1000;
float restarttime = 0;
void loop()
{

  if (millis()<11000 + restarttime){
    fluidize(millis());
  }
 
  
  if (millis() > 11500 + restarttime and notcompleted){
    motor2.brake();

    digitalWrite(14,LOW);
    openLoopDriveRP(DOWN,0.5 , 0.25, 64);
    delay(500);
    openLoopDriveRP(UP, 0.5, 2, 16);  
    delay(500);
    openLoopDriveTED(UP, 0.25, 0.25, 64);
    delay(500);
    TEDDCM(DOWN, 5); // for now just running for 5s
    delay(500);
    openLoopDriveTED(UP, 0.5, 0.25, 64);
    delay(500);
    TEDDCM(UP, 5); // for now just running for 5s
    delay(500);
    openLoopDriveTED(DOWN, 0.75,  1, 64);
    delay(500);
    //notcompleted = false;
    delay(10000); //wire up

    restarttime = millis();
  }




//  fluidize();

  
 

}
