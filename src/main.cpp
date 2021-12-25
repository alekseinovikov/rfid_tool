#include <Arduino.h>
#include "modes.h"

Modes modes;

void setup()
{
  modes.init();
}

/*
 * Main loop.
 */
void loop()
{
  modes.run();
}
