/*
  Author: HPU MInds, Jacob Brittain
  Date: 01/22/2025
  Description: Testing and implementation program to have the hardware talk to HPU Minds Fear project

*/

#define Yellow A0 //defines the pin for the yellow wire to be hooked up to
int sensorValue=0;
int gsr_average=0;

long highValue = 0; 
long lowValue = 0;
long steadyValue = 0;
long heartRate = 0;
const long elevated = 100; // I googled this and the web told me 100 is elevated heartrate
//temporary values to be changed in later versions, currently included so that the structure of how the program
//will be implemented can be established and the only changes will be the values of these variables

const int degreeOfFlux = 20; 
// variable to define how far off of the set steady value is still concidered steady, to be defined in later versions

//variables to define the characters that are going to be sent for controlling behavior
const char highStressChar = 'h';
const char lowStressChar = 'l';
const char regularStressChar = 'r';
//const char deviceControlChar4 = 20;
const char somethingWrong = 'p';
const char confirmation = '2';
const char end = 0;

void setup() {
  Serial.begin(9600); // begins serial communication in the com port its connected to



  const char ping = 5;//ping character is ASCII 5 which is the Enquiry character
  //It wont be changed, so it is set as a constant variable

  char response = 0; //creates a variable to read into and initializes it to the null character (ASCII 0)

  pinMode(10, INPUT_PULLUP); //gives button to press to say that everything is hooked up correctly - gives time to put on gsr before you start
  bool pushed = HIGH; // halts the code until a button connected to pin 10 is pressed in order to allow the heartrate monitor and GSR to be set up
  while(pushed != LOW){
    pushed = digitalRead(10);
  } 

  /*
    INSERT ANY CODE FOR SETTING UP HEART RATE MONITOR HERE
  */
  
  while(!Serial){} //holds code until the serial port is connected

  sendMsg('1'); // sends the ping charater through the serial connection

  /*
    IMPORTANT

    In order for the code to do anything, there needs to be code on the program that this is talking to to both
    wait for character 5, and then respond with character 6, and then wait for character 6 to be sent back in
    order to verify a connection has been established BEFORE it trys to read in any input or data from the Serial
    port or else it will throw a bunch of errors and read in a lot of junk information
  */


  while (response != confirmation){ 
    //holds the code in a loop until the ASCII Acknowledge character(character 6) is read in
    if(Serial.available()>0){
      //makes sure that there is a character in the serial buffer to read in and its not reading in random junk signals
      response = Serial.read();//reads the next character in the serial buffer and stores it in Response
    }
  }

  sendMsg(confirmation); // sends back the response to acknowledge that communication is established

  takeBaseline();
  
}

  int iteration = 0; // global variables required for calculation and sending serial info
  long aver = 0;

void loop() {
  
  int hold_num = 0;
  int tally = 0;
  long sum=0;

  for(int i=0;i<100;i++)           //Average the 100 measurements to remove the glitch
      {
      sensorValue=analogRead(Yellow); //reads the sensor's value
      
      sum += abs(sensorValue); //makes sure that negative readings do not mess with measurement

      if (hold_num == abs(sensorValue)){ // checks if the last value is equal to the current value being read in
        tally++; // if they are the same, iterates a tally
      }
      else{
        tally = 0; // if they are ever not the same back to back, zeroes out the tally
      }
      
      if (tally == 90) //if the same number is ever sent 90 times in a row, sends a negative response because something is broken
      {
        sendMsg('p');
      }

      hold_num = abs(sensorValue);

      /*
        INSERT HEARTRATE MONITOR CODE HERE
      */
      
      delay(1);
      }
   gsr_average = sum/100; //averages the sums of the values

   long Serial_calibration=510; //510 was the baseline reading of the sensor with nothing hooked up 

  long human_resistance = (((1024 + 2 * gsr_average) * 10000)/(Serial_calibration - gsr_average));
  //formula from the webside

  long reading = (abs(human_resistance)); 
  //removes the fluctuation of positive/negative readings
  //the sensor would output both positive and negative values with the same amplitude
  

 
  

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

    } else {
      control = 2; // looks for regular amount of stress
    } 

    switch(control){
      case 0:
        sendMsg(highStressChar); //Device control 1 character - sends high stress

        break;
      case 1:
        sendMsg(lowStressChar); //Device control 2 character - sends low stress

        break;
      case 2:
        sendMsg('r'); //Device control 3 character - sends normal stress
        break;

      default: 
        sendMsg('p'); //negative acknowledge character
        // used to show that something is very wrong with the person hooked up to the sensors, or there is some connection error with hardware
        break;
    }

    aver = 0; //resets variables for next few cycles
    heartRate = 0;
  }
  

}

void sendMsg(char msg){
  Serial.print(msg); // small function to force any print statements into the specific syntax the UE plugin requires to read strings;
  Serial.print(end);
}

void takeBaseline(){
  // rough Idea of a baseline gathering code, feel free to change/improve on it, also lacking implementation for heart rate monitor
  long sum=0;
  for (int i = 0; i <500; i ++){
    sensorValue=analogRead(Yellow); //reads the sensor's value
      
    sum += abs(sensorValue); //makes sure that negative readings do not mess with measurement
    delay(1);
  }
  gsr_average = sum/500; //averages the sums of the values

  long Serial_calibration=510; //510 was the baseline reading of the sensor with nothing hooked up 

  long human_resistance = (((1024 + 2 * gsr_average) * 10000)/(Serial_calibration - gsr_average));
  //formula from the webside

  steadyValue = (abs(human_resistance));
  // lets discuss and change these values next meeting, they're in here as placeholders for until then
  highValue = steadyValue + degreeOfFlux; // I only ballparked these numbers, lets fine tune
  lowValue = steadyValue - degreeOfFlux;



  gsr_average=0;
  sensorValue=0;

}