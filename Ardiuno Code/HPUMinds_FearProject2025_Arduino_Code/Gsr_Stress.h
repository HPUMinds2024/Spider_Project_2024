/*
  Gsr_Fear.h - Library for GSR reading and interpretation in regards to fear/stress.
  Created by Jacob Larson Brittain, February 26, 2025.
  
*/
#ifndef GSRSTRESS_H
#define GSRSTRESS_H

#include <Arduino.h>

class Gsr_Stress
{
  public:
    void begin(int pin);
    void sendMsg(char msg);
    long takeBaseline();
    long takeGsrReading();
  private:
    //unsigned int inPin;
};

#endif