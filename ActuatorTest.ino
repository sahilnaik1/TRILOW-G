#include <SPI.h>
#include <HighPowerStepperDriver.h>
#include <Encoder.h>
#include <SD.h>

#include "Motors.h"

void setup()
{
  SPI.begin();
  
  initializeRP();
  initializeTED();

  initializeTEDDCM();
}

void loop()
{

  openLoopDriveRP(DOWN,0.25 , 0.25, 128);
  delay(500);
  openLoopDriveTED(DOWN, 0.25, 0.25, 128);
  delay(500);

  /*
  TEDDCM(CW, 180, 25);
  delay(500);
  TEDDCM(CCW, 5000, 255);
  delay(500);
  */

  openLoopDriveRP(UP, 0.25, 2, 16);
  delay(500);
  openLoopDriveTED(UP, 0.25, 2, 16);
  delay(500);

  delay(5000);

}
