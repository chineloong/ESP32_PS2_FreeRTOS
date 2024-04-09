#include "stepping_motor.h"
#include "arduino.h"
#include "ESP32Servo.h"

Servo mainServo;//开合舵机
Servo Servo2;



const int freq = 5000;//设置频率
const int ledChannel = 0;//通道号，取值0 ~ 15
const int resolution = 8;//计数位数，取值0 ~ 20

void motor_init(void)
{
    Serial2.begin(115200);
    mainServo.attach(mainServoPin);
    Servo2.attach(ServoPin);
    mainServo.write(0);
    Servo2.write(0);

    pinMode(mainmotorpin1,OUTPUT);
    pinMode(mainmotorpin2,OUTPUT);
    pinMode(dirmotorpin1,OUTPUT); 
    pinMode(dirmotorpin2,OUTPUT);
    pinMode(smallmotorpin1,OUTPUT);
    pinMode(smallmotorpin2,OUTPUT);


    
    // configure LED PWM functionalitites
     ledcSetup(ledChannel, freq, resolution);
  
    // attach the channel to the GPIO to be controlled
    ledcAttachPin(speedPin, ledChannel);//将 LEDC 通道绑定到指定 IO 口上以实现输出
    Serial.printf("motor init \r\n");
}

/********
 * 函数名：
 * 参数：
 * 作用：
 * ********/
void motor_enable(uint8_t num,uint8_t startflag)
{

    //指令
    //电机ID，固定，固定，使能状态，多机状态，校验
    uint8_t order[] = {num,0xF3,0xAB,startflag,0x00,0x6B};
    short size;
    size = sizeof(order)/sizeof(order[1]);
    char hexBuffer;

    for(int i = 0;i<size;i++)
    {
       Serial2.print(order[i], HEX);  

    }
    Serial2.println(size);
    

}

/********
 * 函数名：motor_speed()
 * 参数：dir为方向，00顺时针，01逆时针,acc从0-255,0为直接启动
 * 作用：
 * ********/
void motor_speed(uint8_t num,uint8_t dir,uint16_t speed,uint8_t acc)
{

    //指令
    //电机ID，固定，方向，速度，加速度，多机同步，校验
    uint8_t order[] = {num,0xF6,dir,(speed>>8)&0xFF,(speed)&0xFF,acc,0x00,0x6B};
    short size;
    size = sizeof(order)/sizeof(order[1]);
    Serial2.write(order,size);
}


/********
 * 函数名：motor_pos()
 * 参数：dir为方向，00顺时针，01逆时针，distance 16细分3200一圈 flag绝对还是相对，00为相对
 * 作用：
 * ********/
void motor_pos(uint8_t num,uint8_t dir,uint16_t speed,uint8_t acc,uint32_t distance,uint8_t flag)
{
    //指令
    //电机ID，固定，方向，速度，加速度，距离，多机同步，校验
    int16_t wave;
    // wave = (int)(200.0f/360.0f*distance);
    uint8_t order[] = {num,0xFD,dir,(speed>>8)&0xFF,(speed)&0xFF,acc,
                    (distance>>24)&0xFF,(distance>>16)&0xFF,(distance>>8)&0xFF,
                    (distance)&0xFF,flag,0x00,0x6B};
    short size;
    size = sizeof(order)/sizeof(order[1]);
    Serial2.write(order,size); 

}

/**
电机驱动函数
speed范围0-100
**/
void motor(short speed,short dir,short ena,short pin1,short pin2)
{
  if(speed!=0 && (pin1 == 25 || pin1 == 33))
    //ledcWrite(ledChannel,speed);

  if(ena == 0)
  {
    digitalWrite(pin1,HIGH);
    digitalWrite(pin2,HIGH);
  }
  else 
  {
    if(dir)
    {
      digitalWrite(pin1,HIGH);
      digitalWrite(pin2,LOW);

    }
    else
    {
      digitalWrite(pin1,LOW);
      digitalWrite(pin2,HIGH);
    }
  }
}
