/*
  Gsr_Fear.h - Library for GSR reading and interpretation in regards to fear.
  Created by Jacob Larson Brittain, February 26, 2025.
  
*/
#ifndef GSRFEAR_H
#define GSRFEAR_H

#include <Arduino.h>

class Gsr_Fear
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