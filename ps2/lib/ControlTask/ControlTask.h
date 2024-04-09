#ifndef _CONTROLTASK__H
#define _CONTROLTASK__H

#define FORWARD 0
#define BACKWARD 1
#define TURNL 2
#define TURNR 3
#define XM 4
#define XP 5
#define YP 6
#define YM 7
#define ZP 8
#define ZM 9
#define MAINOPEN 10
#define MAINCLOSE 11
#define MAINWORK 12
#define EARTH 13
#define STOP 14

extern short order;
// enum ORDER
// {
//     FORWARD = 0,
//     BACKWARD = 1,
//     TURNL = 2,
//     TURNR = 3,
//     XM = 4,
//     XP = 5,
//     YP = 6,
//     YM = 7,
//     ZP = 8,
//     ZM = 9,
//     MAINOPEN = 10,
//     MAINCLOSE = 11,
//     MAINWORK = 12,
//     EARTH = 13,
//     STOP = 14,
// };
// extern enum ORDER order;

void ControlTask( void * parameter);
#endif

