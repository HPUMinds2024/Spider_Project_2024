/*----------------------------------------------------------------------
| File Name: UESerial.h
| Programmer: Jacob Larson Brittain
| Date: March 3, 2025
| Description:Library for communication with Unreal Engine Serial plugin
| 
| extra files: 
----------------------------------------------------------------------*/

#ifndef UESerial_H
#define UESerial_H

#include <Arduino.h>

class UESerial {
  public:
      void begin();
        // Begins the serial connection and also sends the ping-response protocol
        // It sends "?" and is looking for "y" from the ue program to confirm a connection has been established

      void sendMsg(char msg);
      void sendMsg(String msg);
      void sendMsg(long msg);
      void sendMsg(int msg);
        // a group of overloaded message sending member functions
        // it will send chars and strings by just sending the message then bookending it with character 0 (null)
        // it sends longs and ints by first sending the datatype as a sting, character 0, then the actual data, then character 0
        // postcondition: the message is converted into the format that the UE plugin requires, then it is sent to the Serial port

      int readInt();
        // postcondition: reads an integer value from the Serial Buffer and returns it

      char readChar();
        // postcondition: reads a byte from the Serial Buffer, converts it into the corresponding char, then returns it

      String readString();
        // postcondition: reads a string from the Serial Buffer, trims it, then returns it

      long readLong();
        // postcondition: reads a float value from the Serial Buffer, converts it to a long, then returns it

  private:

      //

};

#endif