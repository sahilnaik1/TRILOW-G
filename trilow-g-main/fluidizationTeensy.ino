#include <Wire.h>


#include <SparkFun_TB6612.h>


#define AIN1 16
#define AIN2 17
#define STBY 9
#define PWMA 5

const int offsetA = 1;


Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

void setup() {
  Wire.begin();
  // put your setup code here, to run once:
  pinMode(14, OUTPUT); //MOSFET to turn on/off 24V channel
  pinMode(33, OUTPUT); //Input signal for pressure regulator
  Serial.begin(9600);
}

int reading = 0;
void loop() {
  // step 1: instruct sensor to read echoes

  Wire.beginTransmission(40); // transmit to device #112 (0x70)

  // the address specified in the datasheet is 224 (0xE0)

  // but i2c addressing uses the high 7 bits so it's 112

  Wire.write(byte(0x00));      // sets register pointer to the command register (0x00)

  //Wire.write(byte(0x50));      // command sensor to measure in "inches" (0x50)

  // use 0x51 for centimeters

  // use 0x52 for ping microseconds

  Wire.endTransmission();      // stop transmitting

  // step 2: wait for readings to happen

  delay(70);                   // datasheet suggests at least 65 milliseconds

  // step 3: instruct sensor to return a particular echo reading

  Wire.beginTransmission(40); // transmit to device #112

  Wire.write(byte(0x02));      // sets register pointer to echo #1 register (0x02)

  Wire.endTransmission();      // stop transmitting

  // step 4: request reading from sensor

  Wire.requestFrom(40, 2);    // request 2 bytes from peripheral device #112

  // step 5: receive reading from sensor

  if (2 <= Wire.available()) { // if two bytes were received

    reading = Wire.read();  // receive high byte (overwrites previous reading)

    reading = reading << 8;    // shift high byte to be high 8 bits

    reading |= Wire.read(); // receive low byte as lower 8 bits

    Serial.println(reading);
    float psi = (reading / 16383.0) * 150.0;
    
    if (psi <= 300){
      Serial.print("psi: ");
      Serial.println(psi);// print the reading
  
    }
    
  }
            

  analogWrite(33, 100);  
  //TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz

  int sensorVal = analogRead(A4);
  float voltage = sensorVal * (100.0 / 1023.0);
  //Serial.print("sensorVal: ");
  //Serial.println(sensorVal);
  //Serial.print("voltage: ");
  //Serial.println(voltage);
  //motor1.drive(-100);
  //motor1.drive(-200, 5000);


  // put your main code here, to run repeatedly:
  /*
  digitalWrite(14, HIGH); //open valve for short burst fluidization
  delay(1000); //open for 50ms TBD
  digitalWrite(14,LOW);
  delay(1000);
  */
}
