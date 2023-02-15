#include "D_ObjectsAndParameters.h"

namespace TOOL
{
  unsigned long TIME(void (*function)()) //runs function and return execution time in microseconds
  {
    unsigned long t0, tf;
    
    t0 = micros();
    function();
    tf = micros();
    
    return tf - t0;
  }
  
  void DO(void (*Thing)(), const double Frequency = 1000.0) //performs Thing at Frequency if possible, otherwise performs Thing as fast as possible
  {
    static const unsigned long deltaT = 1000000.0 / Frequency;
    
    static const unsigned long refT =  micros();
    static unsigned long reps = 0u;
    unsigned long tf = micros();
    
    if(tf < refT + (reps + 1u) * deltaT) return;
    else
    {
      Thing();
      //unsigned long oldReps = reps;
      reps = (micros() - refT) / deltaT;
      //for(uint8_t i = 0; i < reps - oldReps - 1; i++) Thing();
    }
  }
  
  void HALT() //halts microcontroller operation
  {
    while(1){}
  }
  
  void FLAG() //prints flag to serial console to determine if a certain part of program has been reached
  {
    Serial.print(" [#] ");
  }
}
