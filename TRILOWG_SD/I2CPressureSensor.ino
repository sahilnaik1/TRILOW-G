// Pressure sensor 

#include <Wire.h>

float a, b, Output, Pressure;
const long OutMax = 14745, OutMin = 1638;
const long PressureMax = 150, PressureMin = 0; //Inches of H20

void setup() {
  Wire.begin(0x28);

  Serial.begin(9600);
}

void loop() {
  Wire.requestFrom(0x28, 2);
   a = Wire.read();
   b = Wire.read();
  Output = BitShiftCombine(a , b);

  Pressure = (((Output - OutMin) * (PressureMax - PressureMin)) / (OutMax - OutMin)) + PressureMin;

  Serial.println(Output); //Inches of H20
  delay(100);

}

long BitShiftCombine( unsigned char x_high, unsigned char x_low)
{
  long combined;
  combined = x_high;              //send x_high to rightmost 8 bits
  combined = combined << 8;       //shift x_high over to leftmost 8 bits
  combined |= x_low;              //logical OR keeps x_high intact in combined and fills in rightmost 8 bits
  return combined;
}
