#include "MyPS2.h"
#include "Arduino.h"

void FreeRTOS_Init(void)
{
    TaskHandle_t PS2_TaskHandle;//声明一个TaskHandle_t类型的变量，用于存储将要新建的任务的句柄
    xTaskCreate(
                PS2_Task,          /*任务函数*/
                "PS2_Task",        /*带任务名称的字符串*/
                10000,            /*堆栈大小，单位为字节*/
                NULL,             /*作为任务输入传递的参数*/
                6,                /*任务的优先级*/
                &PS2_TaskHandle);            /*任务句柄*/
    Serial.print("taskOne任务的优先级 = ");

}