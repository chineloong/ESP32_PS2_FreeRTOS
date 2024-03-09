#include "Arduino.h"
#include "PS2X_lib.h" //for v1.6
#include "MyPS2.h"
#include "Task.h"


void setup()
{
   // added delay to give wireless ps2 module some time to startup, before configuring it
  delay(500);
  PS2_Init();
  
  FreeRTOS_Init();

  
}

void loop()
{
}
