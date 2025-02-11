/*
  Author: HPU MInds, Jacob Brittain
  Date: 01/22/2025
  Description: Testing and implementation program to have the hardware talk to HPU Minds Fear project

*/

#define Yellow A0 //defines the pin for the yellow wire to be hooked up to
int sensorValue=0;
int gsr_average=0;

const long highValue = 0; 
const long lowValue = 0;
const long steadyValue =0;
//temporary values to be changed in later versions, currently included so that the structure of how the program
//will be implemented can be established and the only changes will be the values of these variables

const int degreeOfFlux = 0; 
// variable to define how far off of the set steady value is still concidered steady, to be defined in later versions

void setup() {
  Serial.begin(9600); // begins serial communication in the com port its connected to



  const char ping = 5;//ping character is ASCII 5 which is the Enquiry character
  //It wont be changed, so it is set as a constant variable

  char response = 0; //creates a variable to read into and initializes it to the null character (ASCII 0)
  
  while(!Serial){} //holds code until the serial port is connected

  Serial.print(ping); // sends the ping charater through the serial connection

  /*
    IMPORTANT

    In order for the code to do anything, there needs to be code on the program that this is talking to to both
    wait for character 5, and then respond with character 6, and then wait for character 6 to be sent back in
    order to verify a connection has been established BEFORE it trys to read in any input or data from the Serial
    port or else it will throw a bunch of errors and read in a lot of junk information
  */


  while (response != 6){ 
    //holds the code in a loop until the ASCII Acknowledge character(character 6) is read in
    if(Serial.available()>0){
      //makes sure that there is a character in the serial buffer to read in and its not reading in random junk signals
      response = Serial.read();//reads the next character in the serial buffer and stores it in Response
    }
  }

  Serial.print(response); // sends back the response to acknowledge that communication is established
  
}
int iteration = 0;
long aver = 0;
void loop() {
  
  long sum=0;
  for(int i=0;i<100;i++)           //Average the 100 measurements to remove the glitch
      {
      sensorValue=analogRead(Yellow); //reads the sensor's value
      //sensorValue -=510;
      
      sum += abs(sensorValue); //makes sure that negative readings do not mess with measurement
      delay(1);
      }
   gsr_average = sum/100; //averages the sums of the values

   long Serial_calibration=510; //510 was the baseline reading of the sensor with nothing hooked up 

  long human_resistance = (((1024 + 2 * gsr_average) * 10000)/(Serial_calibration - gsr_average));
  //formula from the webside

  long reading = (abs(human_resistance)); 
  //removes the fluctuation of positive/negative readings
  //the sensor would output both positive and negative values with the same amplitude
  
  
  //Serial.println(reading);
  
  
  //this block averages every 10 readings and sends the report of either elevated, dropped, or steady
  //readings through the serial port using 3 of the 4 device control ASCII characters
  iteration ++; 
  aver += reading;
  if (iteration == 10){
    iteration = 0;
    aver = aver/10;

    /*
      IMPORTANT

      The program MUST be waiting to recieve the Device control characters in order to modify behavior/output in
      some way or else this will not do anything. It will output the characters, but the recieving program will
      not do anything in response because it is not waiting to recieve the commands sent to it.
    
    */

    if (aver >= highValue){
      Serial.print(17); //Device control 1 character
    } else{
      if (aver <= lowValue){
        Serial.print(18); //Device control 2 character
      }else{
        if ((aver <= steadyValue+degreeOfFlux) && (aver >= steadyValue-degreeOfFlux)){
          Serial.print(19); //Device control 3 character
        }
      }

    }

  }
  

}
