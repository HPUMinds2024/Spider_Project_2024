/*----------------------------------------------------------------------
| File Name: HPUMinds_FearProject2025_Arduino_Code.ino
| Programmer: HPU MInds, Jacob Larson Brittain
| Date: 01/22/2025
| Description:Testing and implementation program to have the hardware 
| talk to HPU Minds Fear project
| extra files: Gsr_Stress.h
----------------------------------------------------------------------*/

#include "Gsr_Stress.h"
#include "UESerial.h"
#define Yellow 0 //defines the pin for the yellow wire to be hooked up to

const int degreeOfFlux = 20; 
// variable to define how far off of the set steady value is still concidered steady, to be defined in later versions

long highValue = 0; 
long lowValue = 0;
long steadyValue = 0;
long heartRate = 0;
const long elevated = 100; // I googled this and the web told me 100 is elevated heartrate
//temporary values to be changed in later versions, currently included so that the structure of how the program
//will be implemented can be established and the only changes will be the values of these variables

//variables to define the characters that are going to be sent for controlling behavior
const char highStressChar = 'h';
const char lowStressChar = 'l';
const char regularStressChar = 'r';
//const char deviceControlChar4 = 20;
const char somethingWrong = 'p';
const char confirmation = '2';
const char end = 0;

Gsr_Stress gsr;
UESerial ue;

void setup() {
  ue.begin(); // begins serial communication in the com port its connected to

  gsr.begin(Yellow);

    //const char ping = 5;//ping character is ASCII 5 which is the Enquiry character
    //It wont be changed, so it is set as a constant variable

  char response = 0; //creates a variable to read into and initializes it to the null character (ASCII 0)

  int buttonPin = 10;
  pinMode(buttonPin, INPUT_PULLUP); //gives button to press to say that everything is hooked up correctly - gives time to put on gsr before you start
  bool pushed = HIGH; // halts the code until a button connected to pin 10 is pressed in order to allow the heartrate monitor and GSR to be set up
  while(pushed != LOW){
    pushed = digitalRead(buttonPin);
  } 

  /*
    INSERT ANY CODE FOR SETTING UP HEART RATE MONITOR HERE
  */
  
  while(!Serial){} //holds code until the serial port is connected

  ue.sendMsg('1'); // sends the ping charater through the serial connection

  /*
    IMPORTANT

    In order for the code to do anything, there needs to be code on the program that this is talking to to both
    wait for character 5, and then respond with character 6, and then wait for character 6 to be sent back in
    order to verify a connection has been established BEFORE it trys to read in any input or data from the Serial
    port or else it will throw a bunch of errors and read in a lot of junk information
  */


  while (response != confirmation){ 
    //holds the code in a loop until the ASCII Acknowledge character(character 6) is read in
    response = ue.readInt();
  }

  ue.sendMsg(confirmation); // sends back the response to acknowledge that communication is established
  
  steadyValue = gsr.takeBaseline();
  if (steadyValue == -1){
    ue.sendMsg(somethingWrong);
  }
  
  highValue = steadyValue + degreeOfFlux; 
  lowValue = steadyValue - degreeOfFlux;  
}

int iteration = 0; // global variables required for calculation and sending serial info
long aver = 0;

void loop() {
  
  long reading =  gsr.takeGsrReading(); //take the gsr reading
  if (reading == -1){
    ue.sendMsg(somethingWrong);
  }
  //this block averages every 10 readings and sends the report of either elevated, dropped, or steady readings.
  //sends through the serial port using 3 of the 4 device control ASCII characters as well as Negative Acknowledge (in case of issue/unexpected behavior)
  iteration ++; 
  aver += reading;
  if (iteration == 10){
    iteration = 0;
    aver = aver/10;
    heartRate = heartRate/10;

    /*
      IMPORTANT

      The program MUST be waiting to recieve the Device control characters in order to modify behavior/output in
      some way or else this will not do anything. It will output the characters, but the recieving program will
      not do anything in response because it is not waiting to recieve the commands sent to it.
    
    */ 
    int control = -1;

    if ((aver <= lowValue) || (heartRate >= elevated)){
      control = 0; // looks for indication of High Stress 

    }else if (aver >= highValue){
      control = 1; // looks for exceptionally low stress 

    } else if ((aver > lowValue) && (aver < highValue) && (heartRate < elevated)){
      control = 2; // looks for regular amount of stress
    } else {
      control = -1;
    }

    switch(control){
      case 0:
         ue.sendMsg(highStressChar); //Device control 1 character - sends high stress
        break;
      case 1:
         ue.sendMsg(lowStressChar); //Device control 2 character - sends low stress
        break;
      case 2:
         ue.sendMsg(regularStressChar); //Device control 3 character - sends normal stress
        break;
      default: 
         ue.sendMsg(somethingWrong); //negative acknowledge character
        break; // used to show that something is very wrong with the person hooked up to the sensors, or there is some connection error with hardware
    }
    aver = 0; //resets variables for next few cycles
    heartRate = 0;
  }
}

