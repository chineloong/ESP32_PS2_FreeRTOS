#include "Arduino.h"
#include "PS2X_lib.h" //for v1.6
#include "MyPS2.h"
#include "Task.h"
#include "stepping_motor.h"
#include <ESP32Servo.h>

int pos = 0;
Servo myservo;


void setup()
{
   // added delay to give wireless ps2 module some time to startup, before configuring it
  delay(500);
  Serial.begin(115200);
  //PS2_Init();
  motor_init();
 // FreeRTOS_Init();
  myservo.attach(4, 500, 2500);          //修正脉冲宽度
  
}

void loop()
{

  // for (pos = 0; pos <= 180; pos += 1) {       //pos+=1等价于pos=pos+1
  //   myservo.write(pos);
  //   delay(15);					
  // }
  // for (pos = 180; pos >= 0; pos -= 1) {
  //   myservo.write(pos);
  //   delay(15); 
  // }
  Serial.print("done");
  // motor_pos(1,0,1000,300,3200000,0);
  // delay(10000);
  // motor_pos(1,0,1000,300,0,1);
  // delay(10000);
  // motor_speed(1,1,1000,300);
  // delay(5000);
  // motor_speed(1,1,0,300);
  // delay(5000);
}
