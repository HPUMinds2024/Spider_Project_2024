/*----------------------------------------------------------------------
| File Name: Gsr_Stress.cpp
| Programmer: Jacob Larson Brittain
| Date: February 26, 2025
| Description:Library for GSR reading and interpretation in regards to 
| fear/stress.
| extra files: Gsr_Stress.h
----------------------------------------------------------------------*/

#include "Arduino.h"
#include "Gsr_Stress.h"

void Gsr_Stress::begin(int pin)
{
  switch(pin){
    case 0:
      #define inPin A0
      break;
    case 1:
      #define inPin A1
      break;
    case 2:
      #define inPin A2
      break;
    case 3:
      #define inPin A3
      break;
    case 4:
      #define inPin A4
      break;
    case 5:
      #define inPin A5
      break;
  }
}



// a function to take the GSR baseline. There was talk of taking multible baselines trough the code, so I turned it into a function
long Gsr_Stress::takeBaseline(){
  
  long sum=0;

  byte certainty = 5; 
  // a variable to determine how many times to take a gsr reading before we are certain we have a representative baseline
  // currently set to 5

  for (int i = 0; i <certainty; i ++){
    sum += takeGsrReading();
    if (takeGsrReading() == -1){
      return -1;
    }
  }

  long gsr_average = sum / certainty;

  long Serial_calibration=510; //510 was the baseline reading of the sensor with nothing hooked up 

  long human_resistance = (((1024 + 2 * gsr_average) * 10000)/(Serial_calibration - gsr_average));
  //formula from 


  return human_resistance;

  
  /*
    ***INSERT Heart Rate Monitor Code Here***
  */

}

//function to take 100 readings and average them together as one average reading, then returns that average
//if 90 consecutive readings are the same, it decides there's an issue and sends that through serial
long Gsr_Stress::takeGsrReading(){
  int hold_num = 0;
  byte tally = 0;
  long sum=0;

  for(int i=0;i<100;i++) {          //Average the 100 measurements to remove the glitch
  
    long sensorValue=analogRead(inPin); //reads the sensor's value
    
    sensorValue = abs(sensorValue); //makes sure that negative readings do not mess with measurement
    
    sum += sensorValue; 

    if (hold_num == sensorValue){ // checks if the last value is equal to the current value being read in
      tally++; // if they are the same, iterates a tally
    }
    else{
      tally = 0; // if they are ever not the same back to back, zeroes out the tally
    }
    
    if (tally == 90) //if the same number is ever sent 90 times in a row, sends a negative response because something is broken
    {
      return -1;
    }

    hold_num = sensorValue;

    /*
      INSERT HEARTRATE MONITOR CODE HERE
    */
    
    delay(1);
  }
  return sum/100;
}