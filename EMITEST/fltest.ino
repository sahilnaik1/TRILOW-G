#include <TimerOne.h>

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

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

unsigned long myTime;
float t1; //t1 operates timers on Solenoid Valve
float t2; //t2 operates timers on Vibration Motors

float timeOpenSV = 150.0; //ms Solenoid Valve
float timeCloseSV = 100.0; //ms Solenoid Valve
float timeOpenVM = 500.0; //ms Vibration Motor
float timeCloseVM = 1000.0; //ms Vibration Motor
float totalTime = 10.0; //s Fluidization length
bool check = true;
void setup() {
  // put your setup code here,   to run once:
  pinMode(14, OUTPUT); //MOSFET to turn on/off 24V channel
  Serial.begin(9600);
 
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if (float(millis())/1000.0 > totalTime){ // seconds
    digitalWrite(14,LOW);
    motor2.brake();
    exit(0); //exit program after ~totalTime seconds of fluidization
  }
  if (check){
    float t1 = float(millis());
    float t2 = float(millis());
    check = false;
  }
  Serial.println(float(millis()));
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
  
//  digitalWrite(14, HIGH); //open valve for short burst fluidization
//  delay(50); //open for 50ms TBD
//  digitalWrite(14,LOW);
//  delay(100);

//  motor2.drive(200,500);
//  motor2.drive(-200,500);
//  motor2.brake();

}
