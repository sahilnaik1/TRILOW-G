// This is the library for the TB6612 that contains the class Motor and all the
// functions
#include <SparkFun_TB6612.h>
#include <Encoder.h>
#include <SD.h>

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define AIN1 4
//#define BIN1 7
#define AIN2 5
//#define BIN2 8
#define PWMA 6
//#define PWMB 6
#define STBY 9

// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
//Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

Encoder myEnc(11, 12);
IntervalTimer myTimer;
File myFile;

const int encSteps = 10000;

const int chipSelect = BUILTIN_SDCARD;

int loadCell = 0;
int pSensor1 = 0;
int readLoadCell;
int readpSensor1;

void setup()
{
  Serial.begin(115200);
  myTimer.begin(saveData, 1000);
  SD.begin(chipSelect);
}

long oldPosition = -999;
long newPosition = -999;

void loop()
{
  //Use of the drive function which takes as arguements the speed
  //and optional duration.  A negative speed will cause it to go
  //backwards.  Speed can be from -255 to 255.  Also use of the
  //brake function which takes no arguements.
   newPosition = myEnc.read();
  //  motor1.drive(255);
//  myFile = SD.open("data.txt", FILE_WRITE);
  while (newPosition <= encSteps) {
    if (encSteps - newPosition >= 500) {
      motor1.drive(255);
    }
    if (encSteps - newPosition == 200) {
      motor1.drive(105);
    }
    if (encSteps - newPosition == 100) {
      motor1.drive(55);
    }
    if (encSteps - newPosition == 50) {
      motor1.drive(10);
    }
    if (encSteps - newPosition <= 0) {
      motor1.brake();
    }
    newPosition = myEnc.read();
    if (newPosition != oldPosition) {
      oldPosition = newPosition;
            Serial.println(newPosition);
    }
  }
  if (newPosition <= 0) {
    motor1.brake();
  }
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
        Serial.println(newPosition);
  }
//  myFile.close();
}

void saveData(int newPosition, int readLoadCell) {
  newPosition = myEnc.read();
  readLoadCell = analogRead(loadCell);
  readpSensor1 = analogRead(pSensor1);
  myFile = SD.open("data.txt", FILE_WRITE);
  myFile.print(newPosition);
  myFile.print(",");
  myFile.print(newPosition);
  myFile.print(",");
  myFile.print(newPosition);
  myFile.print(",");
  myFile.print(newPosition);
  myFile.print(",");
  myFile.print(newPosition);
  myFile.print(",");
  myFile.print(newPosition);
  myFile.print(",");
  myFile.print(newPosition);
  myFile.print(",");
  myFile.print(99999999);
  myFile.print(",");
  myFile.println(99999999);
  myFile.close();
//  Serial.println(newPosition);
//  Serial.print(",");
//  Serial.print(newPosition);
//  Serial.print(",");
//  Serial.print(newPosition);
//  Serial.print(",");
//  Serial.print(newPosition);
//  Serial.print(",");
//  Serial.print(newPosition);
//  Serial.print(",");
//  Serial.print(newPosition);
//  Serial.print(",");
//  Serial.print(newPosition);
//  Serial.print(",");
//  Serial.print(9999999);
//  Serial.print(",");
//  Serial.println(9999999);
}
