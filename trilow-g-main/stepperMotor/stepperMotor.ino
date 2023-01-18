// This example shows basic use of a Pololu High Power Stepper Motor Driver.
//
// It shows how to initialize the driver, configure various settings, and enable
// the driver.  It shows how to step the motor and switch directions using the
// driver's SPI interface through the library's step() and setDirection() member
// functions.
//
// Since SPI is used to trigger steps and set the direction, connecting the
// driver's STEP and DIR pins is optional for this example.  However, note that
// using SPI control adds some overhead compared to using the STEP and DIR pins.
// In addition, since the library caches SPI register values, SPI control is
// more likely to re-enable the driver with the wrong settings (e.g. current
// limit) after a power interruption, although using the verifySettings() and
// applySettings() functions appropriately can help prevent this.
//
// Before using this example, be sure to change the setCurrentMilliamps36v4 line
// to have an appropriate current limit for your system.  Also, see this
// library's documentation for information about how to connect the driver:
//   http://pololu.github.io/high-power-stepper-driver

#include <SPI.h>
#include <HighPowerStepperDriver.h>
#include <Encoder.h>
#include <SD.h>

const int chipSelect = BUILTIN_SDCARD;
const uint8_t CSPin = 4;
const uint8_t SLPPin = 5;
const uint8_t microstep = 16;
const int loadCell = A0;
const int pSensor1 = A1;

// This period is the length of the delay between steps, which controls the
// stepper motor's speed.  You can increase the delay to make the stepper motor
// go slower.  If you decrease the delay, the stepper motor will go faster, but
// there is a limit to how fast it can go before it starts missing steps.
const uint16_t StepPeriodUs = 67;

HighPowerStepperDriver sd;
Encoder myEnc(2, 3);
File myFile;
IntervalTimer myTimer;
//ADC *adc = new ADC();

int oldPosition = -999;
int newPosition = myEnc.read();
int readLoadCell;
int readpSensor1;

void setup()
{
  Serial.begin(115200);
  SPI.begin();
  sd.setChipSelectPin(CSPin);

  // Give the driver some time to power up.
  delay(10);

  //Reset the driver to its default settings and clear latched status
  // conditions.
  sd.resetSettings();
  sd.clearStatus();

  // Select auto mixed decay.  TI's DRV8711 documentation recommends this mode
  // for most applications, and we find that it usually works well.
  sd.setDecayMode(HPSDDecayMode::AutoMixed);

  // Set the current limit. You should change the number here to an appropriate
  // value for your particular system.
  sd.setCurrentMilliamps36v4(1000);

  // Set the number of microsteps that correspond to one full step.
  sd.setStepMode(HPSDStepMode::MicroStep16);

  // Enable the motor outputs.
  sd.enableDriver();

  SD.begin(chipSelect);

  pinMode(SLPPin, OUTPUT);
  digitalWrite(SLPPin, LOW);

  pinMode(loadCell, INPUT);
  analogReadRes(16);

  myTimer.begin(saveData, 1000);
}

void saveData(int newPosition, int readLoadCell) {
  newPosition = myEnc.read();
  readLoadCell = analogRead(loadCell);
  readpSensor1 = analogRead(pSensor1);
  Serial.print(newPosition);
  Serial.print(",");
  Serial.print(newPosition);
  Serial.print(",");
  Serial.print(newPosition);
  Serial.print(",");
  Serial.print(newPosition);
  Serial.print(",");
  Serial.print(newPosition);
  Serial.print(",");
  Serial.print(newPosition);
  Serial.print(",");
  Serial.print(newPosition);
  Serial.print(",");
  Serial.print(pSensor1);
  Serial.print(",");
  Serial.println(readLoadCell);
}

void loop()
{
  digitalWrite(SLPPin, HIGH);
  //  Serial.println("Sleep Pin High for 5 seconds.");
  delay(10);
  // Step in the default direction 1000 times.
  sd.setDirection(1);
  int startTime = micros();
  while (newPosition <= 30480)
  {
    newPosition = myEnc.read();
    //    myFile = SD.open("data.txt", FILE_WRITE);
    //    myFile.print(newPosition);
    //    myFile.print(",");
    //    myFile.println(readLoadCell);
    if (newPosition != oldPosition) {
      oldPosition = newPosition;
    }
    sd.step();
    delayMicroseconds(StepPeriodUs);
  }
  int currentTime = micros();
  Serial.println(currentTime - startTime);
  //  myFile.close();
  while (true) {
    digitalWrite(SLPPin, LOW);
  }

  //  // Wait for 300 ms.
  //  delay(300);
  //
  //  // Step in the other direction 1000 times.
  //  sd.setDirection(1);
  //  for (unsigned int x = 0; x < 200 * microstep * 3; x++)
  //  {
  //    newPosition = myEnc.read();
  //    if (newPosition != oldPosition) {
  //      oldPosition = newPosition;
  //      Serial.println(newPosition);
  //    }
  //    sd.step();
  //    delayMicroseconds(StepPeriodUs);
  //  }
  //
  //  // Wait for 300 ms.
  //  delay(300);
  //  digitalWrite(SLPPin, LOW);
  //  Serial.println("Sleep Pin Low for 5 seconds.");
  //  delay(5000);
}
