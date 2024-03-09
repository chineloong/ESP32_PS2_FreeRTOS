#ifndef __MYPS2_H
#define __MYPS2_H



/******************************************************************
 * set pins connected to PS2 controller:
 *   - 1e column: original
 *   - 2e colmun: Stef?
 * replace pin numbers by the ones you use
 ******************************************************************/
#define PS2_DAT 19 // MISO  19
#define PS2_CMD 23 // MOSI  23
#define PS2_SEL 5  // SS     5
#define PS2_CLK 18 // SLK   18


/******************************************************************
 * select modes of PS2 controller:
 *   - pressures = analog reading of push-butttons
 *   - rumble    = motor rumbling
 * uncomment 1 of the lines for each mode selection
 ******************************************************************/
// #define pressures   true
#define pressures false
// #define rumble      true
#define rumble false


extern int error;

void PS2_Init(void);
void PS2_Task( void * parameter);
#endif
