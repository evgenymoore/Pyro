#include "alarm.hpp"

AlarmDriver Alarm;

void AlarmDriver::Average::Calculation(uint16_t data)
{
  summ += data; 
  counter++;
  if (counter == 830) /* 10 seconds */ 
  {
    value = summ / counter;
    summ = counter = 0;
    flag = true;
  }
};

