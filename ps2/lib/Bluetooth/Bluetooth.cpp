#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void BLE_Init()
{
    SerialBT.begin("Chineloong"); // 如果没有参数传入则默认是蓝牙名称是: "ESP32"
    SerialBT.setPin("1234");   // 蓝牙连接的配对码
    Serial.printf("BT initial ok and ready to pair. \r\n");
}

void BLE_Task(void* pvParameter)
{
    while(1)
    {
        if (Serial.available())
        {
            SerialBT.write(Serial.read());
        }
        if (SerialBT.available())
        {
            Serial.write(SerialBT.read());
        }
        vTaskDelay(50);
    }
}