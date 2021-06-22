#ifndef ALARM_HPP
#define ALARM_HPP

#include "main.h"

class AlarmDriver
{
public:
  
  enum class PatternState { Ready = 0, Reset, Fault, Delay, Capture } State;
    
  struct Average
  {
  private:
    uint16_t counter;
    uint32_t summ;
  public:
    bool flag;
    uint16_t value;
    
    void Calculation(uint16_t data);
  };
  Average Expectation;
};

extern AlarmDriver Alarm;

#endif