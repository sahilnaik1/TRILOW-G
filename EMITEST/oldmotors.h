#include <SPI.h>
#include <HighPowerStepperDriver.h>
//#include <Encoder.h>
HighPowerStepperDriver RP, TED;
#include <SparkFun_TB6612.h>

#define AIN1 30
#define BIN1 35
#define AIN2 29
#define BIN2 34
#define PWMA 28
#define PWMB 33
#define STBY 32
const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY); // ted
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY); // vibe


const uint8_t ChipSelectRP = 41;
const uint8_t ChipSelectTED = 37;

float t1; //t1 operates timers on Solenoid Valve
float t2; //t2 operates timers on Vibration Motors

float timeOpenSV = 150.0; //ms Solenoid Valve
float timeCloseSV = 100.0; //ms Solenoid Valve
float timeOpenVM = 500.0; //ms Vibration Motor
float timeCloseVM = 1000.0; //ms Vibration Motor
float totalTime = 10.0; //s Fluidization length
bool check = true;

// fluidize
void fluidize(unsigned long currtime){
  float totalTime = currtime + totalTime;
  if (float(millis())/1000.0 > totalTime){ // seconds
 
    return; //exit program after ~totalTime seconds of fluidization
  }
  if (check){
    float t1 = float(millis());
    float t2 = float(millis());
    check = false;
  }
  if (t2 < float(millis()) && float(millis()) < t2 + timeOpenVM){
    motor2.drive(200);
  }
  else if (t2 + timeOpenVM < float(millis()) && float(millis()) < t2 + timeOpenVM + timeCloseVM){
    motor2.brake();
  }

  
  if (t1 < float(millis()) && float(millis()) < t1 + timeOpenSV){
    digitalWrite(14, HIGH);
  }
  else if (t1 + timeOpenSV < float(millis()) && float(millis()) < t1 + timeOpenSV +timeCloseSV){
    digitalWrite(14, LOW);
  }

  
  if (float(millis()) > t1 + timeOpenSV+timeCloseSV) {
    t1 = float(millis());
  }
  if (float(millis()) > t2 + timeOpenVM + timeCloseVM) {
    t2 = float(millis());
  }
}
// stepper
enum Direction : uint8_t
{
    DOWN, UP, CCW, CW
};

void openLoopDriveRP(Direction dir, float dist, float spd = 0.2, uint16_t microStepsPerStep = 32) //dist in inches, spd in inches/second
{
    float stepsPerInch = 508;

    unsigned long int numOfMicroSteps = stepsPerInch * dist * microStepsPerStep;
    int microStepPeriod = 1000000 / (spd * stepsPerInch * microStepsPerStep);

    RP.setStepMode(microStepsPerStep);
    RP.setDirection(dir);

    digitalWrite(40, HIGH);

    for (unsigned long int x = 0; x < numOfMicroSteps; x++)
    {
        RP.step();
        delayMicroseconds(microStepPeriod);
    }

    digitalWrite(40, LOW);
}

void openLoopDriveTED(Direction dir, float dist, float spd = 0.2, uint16_t microStepsPerStep = 32) //dist in inches, spd in inches/second
{
    float stepsPerInch = 508;

    unsigned long int numOfMicroSteps = stepsPerInch * dist * microStepsPerStep;
    int microStepPeriod = 1000000 / (spd * stepsPerInch * microStepsPerStep);

    TED.setStepMode(microStepsPerStep);
    TED.setDirection(dir);

    digitalWrite(36, HIGH);

    for (unsigned long int x = 0; x < numOfMicroSteps; x++)
    {
        TED.step();
        delayMicroseconds(microStepPeriod);
    }

    digitalWrite(36, LOW);
}

void initializeRP()
{
    RP.setChipSelectPin(ChipSelectRP);
    delay(1);

    RP.resetSettings();
    RP.clearStatus();
    RP.setDecayMode(HPSDDecayMode::AutoMixed);
    RP.setCurrentMilliamps36v4(1000);
    RP.enableDriver();
}

void initializeTED()
{
    TED.setChipSelectPin(ChipSelectTED);
    delay(1);

    TED.resetSettings();
    TED.clearStatus();
    TED.setDecayMode(HPSDDecayMode::AutoMixed);
    TED.setCurrentMilliamps36v4(1000);
    TED.enableDriver();
}

/////////////////////////////////////////////////////////////////////////
//  END OF STEPPER CODE
/////////////////////////////////////////////////////////////////////////

//const uint8_t AIN1 = 30;
//const uint8_t AIN2 = 29;
//const uint8_t PWMA = 28;
//const uint8_t STBY = 32;
//const uint8_t offsetA = 1;
//
//const uint8_t EncA = 9;
//const uint8_t EncB = 8;

//Encoder myEnc(EncA, EncB);



long oldPosition  = -999;

enum OffState : uint8_t
{
  STOP, STANDBY
};


void TEDDCM(Direction dir, double dist, short spd = 1.0, OffState os = STOP)
{
    if (dir == DOWN) {
      motor1.drive(55,5000);
      motor1.brake();
      return;
    }
    else if (dir == UP){
      motor1.drive(55,5000);
      motor1.brake();
      return;
    }

}
