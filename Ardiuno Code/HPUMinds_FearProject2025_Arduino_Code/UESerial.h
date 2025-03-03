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
          //

      void sendMsg(char msg);
      void sendMsg(String msg);
      void sendMsg(long msg);
      void sendMsg(int msg);
          //

      int readInt();
          //

      char readChar();
          //

      String readString();
          //

      long readLong();
          //

  private:

      //

};

#endif