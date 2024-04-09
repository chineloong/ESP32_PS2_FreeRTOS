#include "ControlTask.h"
#include "stepping_motor.h"
short order;
extern Servo mainServo;//开合舵机
extern Servo Servo2;

float xPos = 0;
float yPos = 0;
float zPos = 0;


#include "Arduino.h"
void ControlTask( void * parameter)
{

    

    ledcWrite(0,100);
    while(1)
    {
        
        switch (order)
        {
        case FORWARD:
            motor(100,1,1,mainmotorpin1,mainmotorpin2);
            digitalWrite(mainmotorpin1,LOW);
            digitalWrite(mainmotorpin2,HIGH);
            Serial.print("forward");
            vTaskDelay(50);
            break;
        case BACKWARD:
            motor(100,0,1,mainmotorpin1,mainmotorpin2);
            digitalWrite(mainmotorpin1,HIGH);
            digitalWrite(mainmotorpin2,LOW);
            Serial.print("backward");
            vTaskDelay(50);
            break;

        case XP:
            xPos+=60;
            Serial.print("x");
            motor_pos(2,0,255,200,xPos,1);
            vTaskDelay(40);
            break;

        case XM:
            xPos-=60;
            if(xPos<0)
                xPos = 0;
            motor_pos(2,0,255,200,xPos,1);
            Serial.print("x");
            vTaskDelay(40);
            break;

        case YP:
            yPos+=20;
            motor_pos(3,0,155,155,yPos,1);
            Serial.print("y");
            vTaskDelay(50);
            break;

        case YM:
            yPos-=20;
            if(yPos<0)
                yPos = 0;
            motor_pos(3,0,155,155,yPos,1);
            Serial.print("y");
            vTaskDelay(50);
            break;

        case ZP:
            zPos+=20;
            motor_pos(1,1,155,155,zPos,1);
            vTaskDelay(50);
            break;

        case ZM:
            zPos-=20;
            if(zPos<0)
                zPos = 0;
            motor_pos(1,1,155,155,zPos,1);
            vTaskDelay(50);
            break;
            
        case MAINOPEN:
            mainServo.write(20);
            vTaskDelay(50);
            break;

        case MAINCLOSE:
            mainServo.write(0);
            vTaskDelay(50);
            break;

        case MAINWORK:
            Servo2.write(0);
            vTaskDelay(1000);
            Servo2.write(30);
            vTaskDelay(1000);
            Serial.print("mainwork");
            Serial.print("\r\n");
            break;

        case EARTH:
            digitalWrite(smallmotorpin1,HIGH);
            digitalWrite(smallmotorpin2,LOW);
            break;
        default:
            digitalWrite(mainmotorpin1,HIGH);
            digitalWrite(mainmotorpin2,HIGH);
            digitalWrite(smallmotorpin1,HIGH);
            digitalWrite(smallmotorpin2,HIGH);
            break;
        }
        
        
        
        vTaskDelay(5);
    }
}
