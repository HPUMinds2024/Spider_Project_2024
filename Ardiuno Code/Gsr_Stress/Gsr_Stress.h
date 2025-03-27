/*----------------------------------------------------------------------
| File Name: Gsr_Stress.h
| Programmer: Jacob Larson Brittain
| Date: February 26, 2025
| Description:Library for GSR reading and interpretation in regards to 
| fear/stress.
| extra files: 
----------------------------------------------------------------------*/
#ifndef GSRSTRESS_H
#define GSRSTRESS_H

#include <Arduino.h>

class Gsr_Stress {

  public:
    void begin(int pin);
      //Postcondition: sets up the GSR sensor on the Analog pin that was specified (0-5, which corresponds with A0-A5)
      // *IMPORTANT* This Function CANNOT be passed A0. To pass the Analog pin, pass the value of the pin, for A0 the value is 0, for A1 the value is 1, and so on through A5.

    long takeBaseline();
      //Postcondition: takes the reading 5 times, then averages them together and returns the baseline taken

    long takeGsrReading();
      //Postcondition: reads the Gsr sensor 100 times, averages it together, uses that number to calculate the human resistance,
      //  then returns the human resistance calculated

  private:
    //
};

#endif