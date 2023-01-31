#include <HighPowerStepperDriver.h>
#include <SD.h>
#include <Encoder.h>
#include <TimerOne.h>
HighPowerStepperDriver RP, TED;



const uint8_t ChipSelectRP = 41;
const uint8_t ChipSelectTED = 37;

enum Direction : uint8_t
{
    DOWN, UP, CCW, CW
};

void openLoopDriveRP(Direction dir, float dist, float spd = 0.2, uint16_t microStepsPerStep = 32) //dist in inches, spd in inches/second
{
    if (!SD.begin(BUILTIN_SDCARD)) {
      while (1) {
      // No SD card, so don't do anything more - stay stuck here
      }
    }

    File myFile = SD.open("test130v2.txt", FILE_WRITE);
    float stepsPerInch = 508;

    unsigned long int numOfMicroSteps = stepsPerInch * dist * microStepsPerStep;
    int microStepPeriod = 1000000 / (spd * stepsPerInch * microStepsPerStep);
    
    RP.setStepMode(microStepsPerStep);
    RP.setDirection(dir);

    digitalWrite(40, HIGH);


    
    for (unsigned long int x = 0; x < numOfMicroSteps; x++)
    {
        RP.step();
        myFile.print("RP: ");
        delayMicroseconds(microStepPeriod);
    }

    digitalWrite(40, LOW);
}

void openLoopDriveTED(Direction dir, float dist, float spd = 0.2, uint16_t microStepsPerStep = 32) //dist in inches, spd in inches/second
{
    File myFile = SD.open("test130v3.txt", FILE_WRITE);
    float stepsPerInch = 508;

    unsigned long int numOfMicroSteps = stepsPerInch * dist * microStepsPerStep; // total steps to destination
    int microStepPeriod = 1000000 / (spd * stepsPerInch * microStepsPerStep); // time between steps (i/s * steps/i * msteps/steps = s / msteps

    TED.setStepMode(microStepsPerStep);
    TED.setDirection(dir);

    digitalWrite(36, HIGH);

    uint16_t iterate = 0;
    float t1 = micros();
    float print_timer = micros();
    while (iterate < numOfMicroSteps){

      if (micros() >= print_timer + 1) {
        myFile.print("RP: ");
        myFile.println(millis());
        print_timer = micros();
      }
      if (micros() >= t1 + float(microStepPeriod)){
        TED.step();
        iterate +=1;
        t1 = micros();
      }

    }
//
//    for (unsigned long int x = 0; x < numOfMicroSteps; x++)
//    {
//        TED.step();
//        myFile.print("TED: ");
//        delayMicroseconds(microStepPeriod);
//    }

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

const uint8_t IN1 = 30;
const uint8_t IN2 = 29;
const uint8_t PWM = 28;
const uint8_t STBY = 32;

const uint8_t EncA = 9;
const uint8_t EncB = 8;

Encoder myEnc(EncA, EncB);

void initializeTEDDCM()
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(PWM,OUTPUT);
  pinMode(STBY,OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(PWM, HIGH);
  digitalWrite(STBY, HIGH);
}

long oldPosition  = -999;

enum OffState : uint8_t
{
  STOP, STANDBY
};

float readEncDeg()
{
  return myEnc.read() * 0.288;
}

void TEDDCM(Direction dir, float deg, short spd = 63, OffState os = STOP)
{
   float initPos = readEncDeg();
    
  digitalWrite(STBY, HIGH);
  analogWrite(PWM, spd);
  
  if(dir == CCW)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    while((readEncDeg() - initPos) > -deg) continue;
  }
  else
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    while((readEncDeg() - initPos) < deg) continue;
  }
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  analogWrite(PWM, 0);

  if(os == STANDBY) digitalWrite(STBY, LOW);
}
