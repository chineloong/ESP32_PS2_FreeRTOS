#ifndef __STEPPING_MOTOR_H
#define __STEPPING_MOTOR_H

#include "arduino.h"

void motor_init(void);
void motor_enable(uint8_t num,uint8_t startflag);
void motor_speed(uint8_t num,uint8_t dir,uint16_t speed,uint8_t acc);
void motor_pos(uint8_t num,uint8_t dir,uint16_t speed,uint8_t acc,uint32_t distance,uint8_t flag);
#endif
