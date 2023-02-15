#include "C_CustomClasses.h"

Adafruit_ADS1015 ads;
Honeywell_ABP abp0(0x28, 0, 150, "psi", 0);
Honeywell_ABP abp2(0x28, 0, 30, "psi", 2);
File fileSD;
BIG2ARRAY<float, 1000, 10> dynamicLog;

//insert sensor/actuator parameters here


// Stepper Motors

HighPowerStepperDriver RP, TED;
Encoder RPEnc(RPEncA, RPEncB);
Encoder TEDEnc(TEDEncA, TEDEncB);
Encoder myEnc(EncA, EncB);
