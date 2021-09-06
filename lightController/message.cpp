#include "message.h"

const uint8_t bufSize = 128;
char msg[bufSize];
boolean newData = false;
const char start = '`';
const char end = '~';

void readSerial() {
  static boolean recvInProgress = false;
  static uint8_t ndx = 0;
  
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != end) {
        msg[ndx] = rc;
        ndx++;
        if (ndx >= bufSize) {
          ndx = bufSize - 1;
        }
      } else {
        msg[ndx] = '\0';  // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == start) {
      recvInProgress = true;
    }
  }
}

void printSerial() {
  if (newData) {
    Serial.println(msg);
    newData = false;
  }
}
