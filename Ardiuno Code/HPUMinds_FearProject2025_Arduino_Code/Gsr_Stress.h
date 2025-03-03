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

      //Postcondition: sends the message passed to the function, followed by character 0. 
      //  If not a string or char, it sends 2 messages, one with the data type and null, then another with the data and null
      //the function has been overloaded in order to take more datatypes in order to make it more versatile for different
      //  use cases

    long takeBaseline();
      //Postcondition: takes the reading 5 times, then averages them together and returns the baseline taken

    long takeGsrReading();
      //Postcondition: reads the Gsr sensor 100 times, averages it together, uses that number to calculate the human resistance,
      //  then returns the human resistance 

  private:
    //
};

#endif