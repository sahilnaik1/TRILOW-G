#include <SPI.h>
#include <HighPowerStepperDriver.h>
//#include <Encoder.h>
HighPowerStepperDriver RP, TED;

const uint8_t ChipSelectRP = 41;
const uint8_t ChipSelectTED = 37;

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

const uint8_t IN1 = 30;
const uint8_t IN2 = 29;
const uint8_t PWM = 28;
const uint8_t STBY = 32;

const uint8_t EncA = 9;
const uint8_t EncB = 8;

//Encoder myEnc(EncA, EncB);
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

void initializeTEDDCM()
{
//  pinMode(AIN1,OUTPUT);
//  pinMode(AIN2,OUTPUT);
//  pinMode(PWMA,OUTPUT);
//  pinMode(STBY,OUTPUT);
//
//  digitalWrite(AIN1, LOW);
//  digitalWrite(AIN2, LOW);
//  digitalWrite(PWMA, HIGH);
//  digitalWrite(STBY, HIGH);
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

void TEDDCM(Direction dir, double dist, short spd = 1.0, OffState os = STOP)
{

//  double deg = 114.591559 * dist * 4;
//  int pulse = 22.13700572 * spd * 4;
//
//  float initPos = readEncDeg();
//
//    
//  digitalWrite(STBY, HIGH);
//  analogWrite(PWM, spd);
//  
//  if(dir == CCW)
//  {
//    digitalWrite(IN1, HIGH);
//    digitalWrite(IN2, LOW);
//
//    while((readEncDeg() - initPos) > -deg) continue;
//  }
//  else
//  {
//    digitalWrite(IN1, LOW);
//    digitalWrite(IN2, HIGH);
//
//    while((readEncDeg() - initPos) < deg) continue;
//  }
//  
//  digitalWrite(IN1, LOW);
//  digitalWrite(IN2, LOW);
//
//  analogWrite(PWM, 0);
//
//  if(os == STANDBY) digitalWrite(STBY, LOW);
    motor1.drive(155,5000);
    motor1.brake();

}
