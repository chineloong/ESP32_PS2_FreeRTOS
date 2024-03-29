#include "Arduino.h"

// #include "MyPS2.h"
#include "Task.h"
#include "stepping_motor.h"
#include "Bluetooth.h"

int pos = 0;


void setup()
{
  Serial.begin(115200);
  Serial.printf("BT");
  //PS2_Init();
  motor_init();
  Serial.printf("BT1");
  BLE_Init();
  Serial.printf("BT2");
  FreeRTOS_Init();
 
  
}

void loop()
{


}
