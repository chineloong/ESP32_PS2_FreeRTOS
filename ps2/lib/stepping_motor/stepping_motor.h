#ifndef __STEPPING_MOTOR_H
#define __STEPPING_MOTOR_H

#include "arduino.h"
#include "ESP32Servo.h"


#define mainServoPin   12
#define ServoPin     13

#define mainmotorpin1   26
#define mainmotorpin2   27
#define dirmotorpin1 25
#define dirmotorpin2 33
#define speedPin 2

#define smallmotorpin1 32
#define smallmotorpin2 14




extern Servo mainServo;//开合舵机
extern Servo Servo2;

void motor_init(void);
void motor_enable(uint8_t num,uint8_t startflag);
void motor_speed(uint8_t num,uint8_t dir,uint16_t speed,uint8_t acc);
void motor_pos(uint8_t num,uint8_t dir,uint16_t speed,uint8_t acc,uint32_t distance,uint8_t flag);
void motor(short speed,short dir,short ena,short pin1,short pin2);
#endif
