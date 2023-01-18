enum Phase : uint8_t{STANDBY, FLUIDIZATION, LEVELING, RPIN, RPOUT, TEDDETACH, TEDEXPAND, TEDRETRACT, TEDATTACH, PAUSE};

struct DataPoint
{
  //management quantities
  Phase experimentPhase;
  unsigned long systemTime;
  unsigned long phaseTime;

  //experimental quantities
  short rpForce;
  short tedForce;
  int pressure1;
  int pressure2;
};
