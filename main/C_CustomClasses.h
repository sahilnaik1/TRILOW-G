#include "B_Libraries.h"

template<typename type, const unsigned int SMPL, const unsigned int SNSRVL>
class BIG2ARRAY
{
private:
  static type MemoryBlock[SMPL][SNSRVL];
  unsigned int WRTSAMPLE, RDSAMPLE, WRTVALUE, RDVALUE;
  unsigned int writeIndex, readIndex;

public:
  BIG2ARRAY() : WRTSAMPLE{0u}, RDSAMPLE{0u}, WRTVALUE{0u}, RDVALUE{0}
  {
  }
  void resetPointers()
  {
    WRTSAMPLE = RDSAMPLE = WRTVALUE = RDVALUE = 0u;
    writeIndex = readIndex = 0;
  }
  void push(type E)
  {
    if(full()) return;
    MemoryBlock[WRTSAMPLE][WRTVALUE] = E;
    WRTVALUE = (WRTVALUE + 1) % SNSRVL;
    WRTVALUE?0:WRTSAMPLE++;
    writeIndex++;
  }
  type pop()
  {
    type val = MemoryBlock[RDSAMPLE][RDVALUE];
    RDVALUE = (RDVALUE + 1) % SNSRVL;
    RDVALUE?0:RDSAMPLE++;
    readIndex++;
    return val;
  }
  boolean full()
  {
    return WRTSAMPLE >= SMPL;
  }
  boolean flushed()
  {
    return readIndex >= writeIndex;
  }
  void printValues()
  {
    Serial.println();
    for(unsigned int i = 0; i < SMPL; i++)
    {
      for(unsigned int j = 0; j < SNSRVL; j++)
      {
        Serial.print(MemoryBlock[i][j]);
        Serial.print("\t");
      }
      Serial.println();
    }
  }
  void zero()
  {
    for(unsigned int i = 0; i < SMPL; i++)
    {
      for(unsigned int j = 0; j < SNSRVL; j++)
      {
        MemoryBlock[i][j] = 0;
      }
    }
  }
};
template<typename type, const unsigned int SMPL, const unsigned int SNSRVL>
type BIG2ARRAY<type, SMPL, SNSRVL>::MemoryBlock[SMPL][SNSRVL] = {0};
