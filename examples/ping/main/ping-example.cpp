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
    Tip: Run idf.py menuconfig to configure
    pins for UART TX, RX and DIR:
    under "Dynamixel 2 Espressif configuration"
*/

Dynamixel2Espressif dxl(MY_UART, (gpio_num_t)CONFIG_DXL_DIR_PIN);

static const char *TAG = "DXL";

void setup() 
{
    // Set Port baudrate to 1000000bps. This has to match with DYNAMIXEL baudrate.
    dxl.begin(1000000);
    // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
}


static void dxl_task(void *pvParameters)
{
    setup();

    while (true )
    {
        bool ret = dxl.ping(MY_SERVO_ID);
        if (ret == 1)
        {
            ESP_LOGI(TAG, "Yay. Got a response from servo with id: %d", MY_SERVO_ID);
        }
        else 
        {
            ESP_LOGW(TAG, "Hmm... servo with id: %d seems unresponsive", MY_SERVO_ID);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

extern "C" void app_main(void)
{
     xTaskCreate(dxl_task, "dxl task", 16384, NULL, 5, NULL);

    while (true) {
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}