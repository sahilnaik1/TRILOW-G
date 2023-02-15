#include "E_Tools.h"


////////////////////////////////////
// Stepper Motor Functions
///////////////////////////////////


// Stepper is 500 impulses per turn. 
// Encoder records one impulse
// 15mm per revolution
// 2000 encoder impulses per 200 stepper steps

const uint8_t ChipSelectRP = 41;
const uint8_t ChipSelectTED = 37;

enum Direction : uint8_t
{
    DOWN, UP, CCW, CW
};

const uint8_t RPEncA = 23;
const uint8_t RPEncB = 22;


void openLoopDriveRP(Direction dir, float dist, float spd, uint16_t microStepsPerStep = 32) //dist in inches, spd in inches/second
{
    float stepsPerInch = 508;

    unsigned long int numOfMicroSteps = stepsPerInch * dist * microStepsPerStep;
    int microStepPeriod = 1000000 / (spd * stepsPerInch * microStepsPerStep);
    int EncoderImpulses = 5066 * dist; // TBD
    
    RP.setStepMode(microStepsPerStep);
    RP.setDirection(dir);

    digitalWrite(40, HIGH);

    float t1 = micros();
    Serial.println(RPEnc.read());
    int initial_pos = RPEnc.read();
    int curr_pos = initial_pos;
    if (dir == DOWN){
      int final_pos = initial_pos + EncoderImpulses;
      while (curr_pos < final_pos ){    
        if (micros() >= t1 + float(microStepPeriod)){
          RP.step();
          curr_pos = RPEnc.read();
          t1 = micros();
        }
      }
      Serial.println(RPEnc.read());
    }
    else if (dir == UP){
      int final_pos = initial_pos - EncoderImpulses;
      while (curr_pos > final_pos){
         if (micros() >= t1 + float(microStepPeriod)){
          RP.step();
          curr_pos = RPEnc.read();
          t1 = micros();
        }
      }
      Serial.println(RPEnc.read());

    }

    digitalWrite(40, LOW);
}

const uint8_t TEDEncA = 39;
const uint8_t TEDEncB = 38;


void openLoopDriveTED(Direction dir, float dist, float spd, uint16_t microStepsPerStep = 32) //dist in inches, spd in inches/second
{
    float stepsPerInch = 508; 

    unsigned long int numOfMicroSteps = stepsPerInch * dist * microStepsPerStep; // total steps to destination
    int microStepPeriod = 1000000 / (spd * stepsPerInch * microStepsPerStep); // time between steps (i/s * steps/i * msteps/steps = s / msteps
    // Moving very slowly gives 1 inch = ~5066 encoder impulses
    int EncoderImpulses = 5066 * dist; // TBD

    TED.setStepMode(microStepsPerStep);
    TED.setDirection(dir);

    digitalWrite(36, HIGH);


    float t1 = micros();
    Serial.println(TEDEnc.read());
    int initial_pos = TEDEnc.read();
    int curr_pos = initial_pos;
    if (dir == DOWN){
      int final_pos = initial_pos + EncoderImpulses;
      while (curr_pos < final_pos ){    
        if (micros() >= t1 + float(microStepPeriod)){
          TED.step();
          curr_pos = TEDEnc.read();
          t1 = micros();
        }
      }
      Serial.println(TEDEnc.read());
    }
    else if (dir == UP){
      int final_pos = initial_pos - EncoderImpulses;
      while (curr_pos > final_pos){
         if (micros() >= t1 + float(microStepPeriod)){
          TED.step();
          curr_pos = TEDEnc.read();
          t1 = micros();
        }
      }
      Serial.println(TEDEnc.read());
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




/////////
// END
/////////
