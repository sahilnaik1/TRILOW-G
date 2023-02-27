

#include "oldmotors.h"

void setup()
{
  SPI.begin();
  
  initializeRP();
  initializeTED();

  initializeTEDDCM();
}

void loop()
{
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
  TEDDCM(DOWN, 5); // for now just running for 5s
  delay(500);
  openLoopDriveTED(DOWN, 0.75,  1, 64);
  delay(500);
}
