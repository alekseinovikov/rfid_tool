#include <Arduino.h>
#include "modes.h"

Modes modes;


void setup()
{
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial)
    ; // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  modes.init();
}

/*
 * Main loop.
 */
void loop()
{
  modes.run();
}
