/*----------------------------------------------------------------------
| File Name: UESerial.cpp
| Programmer: Jacob Larson Brittain
| Date: March 3, 2025
| Description:Library for communication with Unreal Engine Serial plugin
| 
| extra files: UESerial.h
----------------------------------------------------------------------*/

#include "UESerial.h"
#include "Arduino.h"

void UESerial::begin() {

  const char confirmation = '2';
  char response = 0; //creates a variable to read into and initializes it to the null character (ASCII 0)
  const char ping = '1';

  Serial.begin(9600);//begins serial connection
  while(!Serial){}//holds until Serial connection is connected
  

  sendMsg(ping);//sends '?'

  //Serial.flush(); //holds till message sent

  while (response != confirmation){ 
    //holds the code in a loop until 'y' is read in
    response = Serial.read(); // reads in the next char in the buffer
  }

  sendMsg(confirmation); // sends back the response to acknowledge that communication is established

  //Serial.flush(); // holds till message fully sent

}

// a function to send single character messages to the UE project, it adds the null character at the end because the UE plugin required it
void UESerial::sendMsg(char msg) {
  char end = 0;
  Serial.print(msg); // small function to force any print statements into the specific syntax the UE plugin requires to read strings;
  Serial.print(end);
}

void UESerial::sendMsg(String msg) {
  char end = 0;
  Serial.print(msg); // small function to force any print statements into the specific syntax the UE plugin requires to read strings;
  Serial.print(end);
}
void UESerial::sendMsg(long msg) {
  char end = 0;
  Serial.print("long");
  Serial.print(end);
  Serial.print(msg); // small function to force any print statements into the specific syntax the UE plugin requires to read strings;
  Serial.print(end);
}
void UESerial::sendMsg(int msg) {
  char end = 0;
  Serial.print("int");
  Serial.print(end);
  Serial.print(msg); // small function to force any print statements into the specific syntax the UE plugin requires to read strings;
  Serial.print(end);
}

// **SPECIAL CASE**
void sendMsg(float msg){ 
  char end = 0;
  Serial.print("float");
  Serial.print(end);
  long trunc = msg;
  Serial.print(trunc);
  Serial.print(end);
  long dec = (msg - trunc)*100000;
  Serial.print(dec);
  Serial.print(end);
} // When sending a message, it will send first the word "float" then the number as 2 different whole numbers with a null character between them
  // it sends the whole component first, a null, then the decimal component as a number with upto 5 digits
  // However one implements it, keep in mind the second component is 100000 times larger than it should be

int UESerial::readInt() {
  int read;

  while(Serial.available() == 0) {}  // holds code for serial data in the buffer   
  
  read = Serial.parseInt();
  return read;
}

char UESerial::readChar() {
  char read;

  while(Serial.available() == 0) {}  // holds code for serial data in the buffer
  
  int in = Serial.read();
  read = char(in); // concerts to char value
  return read;
}

String UESerial::readString() {
  while(Serial.available() == 0) {}
  String read = Serial.readString(); 
  read.trim(); // removes any whitespace characters at the end or begining of the string
  return read;
}

long UESerial::readLong() {
  long read;
  while(Serial.available() == 0) {}
  float temp = Serial.parseFloat();
  read = long(temp); // converts to long value
  return temp;
}