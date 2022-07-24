#include "message.h"

const uint8_t bufSize = 128;
char MSG[bufSize];
boolean NEW_DATA = false;
const char start = '`';
const char end = '~';

void readSerial() {
  static boolean recvInProgress = false;
  static uint8_t ndx = 0;
  
  char rc;

  while (Serial.available() > 0 && NEW_DATA == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != end) {
        MSG[ndx] = rc;
        ndx++;
        if (ndx >= bufSize) {
          ndx = bufSize - 1;
        }
      } else {
        MSG[ndx] = '\0';  // terminate the string
        recvInProgress = false;
        ndx = 0;
        NEW_DATA = true;
      }
    }

    else if (rc == start) {
      recvInProgress = true;
    }
  }
}

void printSerial() {
  if (NEW_DATA) {
    Serial.println(MSG);
    NEW_DATA = false;
  }
}
