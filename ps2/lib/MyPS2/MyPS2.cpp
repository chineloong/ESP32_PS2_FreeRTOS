#include "PS2X_lib.h" //for v1.6
#include "Arduino.h"
#include "MyPS2.h"
#include <ESP32Servo.h>
#include "stepping_motor.h"
#include "ControlTask.h"

PS2X ps2x; // create PS2 Controller Class
//(ps2x.Button(PSB_PAD_UP)                    //will be TRUE as long as button is pressed 长按
// ps2x.ButtonPressed(PSB_CIRCLE)              //will be TRUE if button was JUST pressed 按下
// ps2x.ButtonReleased(PSB_SQUARE))            //will be TRUE if button was JUST released  松开
// ps2x.NewButtonState(PSB_CROSS)              //will be TRUE if button was JUST pressed OR released按下或者松开

#define pressures true
// #define pressures   false
#define rumble true
// #define rumble      false

// right now, the library does NOT support hot pluggable controllers, meaning
// you must always either restart your Arduino after you connect the controller,
// or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;

// Reset func
void (*resetFunc)(void) = 0;

void PS2_Init(void)
{

  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0)
  {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType();
  switch (type)
  {
  case 0:
    Serial.println("Unknown Controller type found ");
    break;
  case 1:
    Serial.println("DualShock Controller found ");
    break;
  case 2:
    Serial.println("GuitarHero Controller found ");
    break;
  case 3:
    Serial.println("Wireless Sony DualShock Controller found ");
    break;
  }
}

void PS2_Task(void *parameter)
{

  while (1)
  {
    if (error == 1)
    {
      // skip loop if no controller found
      resetFunc();
    }

    // DualShock Controller
    ps2x.read_gamepad(false, vibrate); // read controller and set large motor to spin at 'vibrate' speed

    vibrate = ps2x.Analog(PSAB_CROSS); // this will set the large motor vibrate speed based on how hard you press the blue (X) button

    //   if (ps2x.NewButtonState())      //will be TRUE if any button changes state (on to off, or off to on)
    // {

    if (ps2x.ButtonPressed(PSB_START))
      Serial.println("Start is being held");
    else if (ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");

    // 方向按下
    if (ps2x.Button(PSB_PAD_UP))
    {
      // will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      order = ZP;
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }

    else if (ps2x.Button(PSB_PAD_DOWN))
    {
      Serial.print("DOWN held this hard: ");
      order = ZM;
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }

    else if (ps2x.Button(PSB_PAD_LEFT))
    {
      Serial.print("LEFT held this hard: ");
      ;
      order = XM;
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }

    else if (ps2x.Button(PSB_PAD_RIGHT))
    {
      Serial.print("Right held this hard: ");
      order = XP;
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }

    // 肩键按下
    else if (ps2x.Button(PSB_L3))
    {
      Serial.println("hello");
      Serial.println("L3 pressed");
    }

    else if (ps2x.Button(PSB_R3))
      Serial.println("R3 pressed");

    else if (ps2x.Button(PSB_L2))
    {
      order = YM;
      Serial.println("L2 pressed");
    }
    else if (ps2x.Button(PSB_R2))
    {
      order = YP;
      Serial.println("R2 pressed");
    }

    // 图形按下
    else if (ps2x.Button(PSB_SQUARE))
    {
      Serial.println("X pressed\n");
    }

    else if (ps2x.Button(PSB_CIRCLE))
    {

      order  = EARTH; 
      Serial.println("B pressed");
    }

    //  }

    else if (ps2x.Button(PSB_TRIANGLE))
    {

      motor(0, 1, 1, dirmotorpin1, dirmotorpin2);
      Serial.println("Y pressed\n");
    }

    else if (ps2x.ButtonPressed(PSB_CROSS))
    {
      order = MAINWORK;
      Serial.println("A pressed");
    }

    // 模拟量
    else if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1))
    {
      // print stick values if either is TRUE
      Serial.print("Stick Values:");
      short up = ps2x.Analog(PSS_LY);

      Serial.print(up, DEC); // Left stick, Y axis. Other options: LX, RY, RX
      Serial.print("\n");
      if (up < 118)
      {
        order = BACKWARD;
      }
      else if (up > 138)
      {
        order = FORWARD;
      }

      else
      {
        order = STOP;
        Serial.print("stop");
      }

      // Serial.print(",");
      // Serial.print(ps2x.Analog(PSS_LX), DEC);
      // Serial.print(",");
      // Serial.print(ps2x.Analog(PSS_RY), DEC);
      // Serial.print(",");
      // Serial.println(ps2x.Analog(PSS_RX), DEC);
    }
    else
      order = STOP;

    vTaskDelay(20);
  }
}