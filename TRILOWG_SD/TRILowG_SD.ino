#include "sdCard.h"

void setup()
{
  Serial.begin(9600);
  Serial.println(initializeSD());
}

void loop()
{
  DataPoint x;
  writeToSD(x);
  delay(1000);

}
