#ifndef MESSAGE_H
#define MESSAGE_H

#include "leds.h"

extern const uint8_t bufSize;
extern char msg[];
extern boolean newData;
extern const char start;
extern const char end;

void readSerial();
void printSerial();

#endif
