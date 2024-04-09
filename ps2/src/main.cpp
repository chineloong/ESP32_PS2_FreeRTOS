#include "Arduino.h"

#include "MyPS2.h"
#include "Task.h"
#include "stepping_motor.h"
#include "Bluetooth.h"

int pos = 0;


void setup()
{
  Serial.begin(115200);
  PS2_Init();
  motor_init();
  BLE_Init();
  FreeRTOS_Init();
 
  
}

void loop()
{


}
