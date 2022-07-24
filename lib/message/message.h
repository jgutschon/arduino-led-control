#ifndef MESSAGE_H
#define MESSAGE_H

#include "leds.h"

extern char MSG[];
extern boolean NEW_DATA;

void readSerial();
void printSerial();

#endif
