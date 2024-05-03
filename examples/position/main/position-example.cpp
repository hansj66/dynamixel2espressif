#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"

#include "dynamixel2espressif.h"
#include "actuator.h"

#define MY_SERVO_ID             3
#define DXL_PROTOCOL_VERSION    2.0
#define MY_UART                 UART_NUM_2

/*
    BEFORE YOU BEGIN:

    1: Run idf.py menuconfig to configure
       pins for UART TX, RX and DIR:
       under "Dynamixel 2 Espressif configuration"
    2: Change the value of MY_SERVO_ID to the ID you have given your test servo.
*/

Dynamixel2Espressif dxl(MY_UART, (gpio_num_t)CONFIG_DXL_DIR_PIN);

void setup() 
{
    // Set Port baudrate to 1000000bps. This has to match with DYNAMIXEL baudrate.
    dxl.begin(1000000);
    // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

    // Turn off torque when configuring items in EEPROM area
    dxl.torqueOff(MY_SERVO_ID);
    dxl.setOperatingMode(MY_SERVO_ID, OP_POSITION);
    dxl.torqueOn(MY_SERVO_ID);
}


static void dxl_task(void *pvParameters)
{
    setup();

    while (true )
    {
        dxl.setGoalPosition(MY_SERVO_ID, 1000);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        dxl.setGoalPosition(MY_SERVO_ID, 500);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

extern "C" void app_main(void)
{
     xTaskCreate(dxl_task, "dxl task", 16384, NULL, 5, NULL);

    while (true) {
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}