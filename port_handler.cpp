#include "port_handler.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "arduino_droppings.h"

static const char * TAG = "PORT HANDLER";

DXLPortHandler::DXLPortHandler()
 : open_state_(false)
{}

/* DXLPortHandler */
bool DXLPortHandler::getOpenState()
{
  return open_state_;
}

void DXLPortHandler::setOpenState(bool state)
{
  open_state_ = state;
}


using namespace DYNAMIXEL;

/* SerialPortHandler */
SerialPortHandler::SerialPortHandler(uart_port_t uart_num, gpio_num_t dir_pin)
 : DXLPortHandler(), uart_num_(uart_num), dir_pin_(dir_pin), baud_(1000000)
{}

void SerialPortHandler::begin()
{
  begin(baud_);
}

void SerialPortHandler::begin(unsigned long baud)
{
  baud_ = baud;
  mbedTXdelayus = 24000000 / baud;
  
    uart_config_t uart_config;
    
  uart_config.baud_rate = int(baud);
  uart_config.data_bits = UART_DATA_8_BITS;
  uart_config.parity = UART_PARITY_DISABLE;
  uart_config.stop_bits = UART_STOP_BITS_1;
  uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
  uart_config.rx_flow_ctrl_thresh = 122;
  uart_config.source_clk = UART_SCLK_DEFAULT;

    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(uart_num_, &uart_config));

    uart_set_mode(uart_num_, UART_MODE_UART);

    // Set UART pins(TX: IO4, RX: IO5, RTS: IO18, CTS: IO19)
    ESP_ERROR_CHECK(uart_set_pin(uart_num_, CONFIG_DXL_TX_PIN, CONFIG_DXL_RX_PIN, UART_PIN_NO_CHANGE , UART_PIN_NO_CHANGE ));

    // Setup UART buffered IO
    const int uart_buffer_size = (1024 * 2);
    // Install UART driver (not using an event queue)
    ESP_ERROR_CHECK(uart_driver_install(uart_num_, uart_buffer_size, uart_buffer_size, 10, NULL, 0));


    // Since we're communicating half fuplex we also have to configure the direction pin
    gpio_config_t io_conf;
    
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    
    ESP_ERROR_CHECK(gpio_config(&io_conf));
    ESP_ERROR_CHECK(gpio_set_level(dir_pin_, LOW));

    setOpenState(true);
}

void SerialPortHandler::end(void)
{
  setOpenState(false);
}

int SerialPortHandler::available(void)
{
  int available = 0;
  ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num_, (size_t*)&available));
  return available;
}

int SerialPortHandler::read()
{
  int ret = 0;
  uart_read_bytes(uart_num_, &ret, 1, portMAX_DELAY);
  return ret;
}

size_t SerialPortHandler::write(uint8_t c)
{
   size_t ret;

  ESP_LOGI(TAG, "Write single: %d", c);

  ESP_ERROR_CHECK(gpio_set_level(dir_pin_, HIGH));
  while(gpio_get_level(dir_pin_) != HIGH)
  {
    // Wait for state change
  }

  ret = uart_write_bytes(uart_num_, &c, 1);
  uart_wait_tx_done(uart_num_, 10 /* 1 RTOS ticks max wait time*/);

  uart_flush(uart_num_);

  // delayMicroseconds(mbedTXdelayus);

  ESP_ERROR_CHECK(gpio_set_level(dir_pin_, LOW));
  while(gpio_get_level(dir_pin_) != LOW)
  {
    // Wait for state change
  }

  return ret;      
}

size_t SerialPortHandler::write(uint8_t *buf, size_t len)
{
  size_t ret;

  ESP_LOGI(TAG, "Write buffer len: %d", len);

  ESP_ERROR_CHECK(gpio_set_level(dir_pin_, HIGH));
  while(gpio_get_level(dir_pin_) != HIGH)
  {
    // Wait for state change
  }

  ret = uart_write_bytes(uart_num_, buf, len);
  uart_wait_tx_done(uart_num_, 10 /* 1 RTOS ticks max wait time*/);

  uart_flush(uart_num_);

  // delayMicroseconds(mbedTXdelayus);

  ESP_ERROR_CHECK(gpio_set_level(dir_pin_, LOW));
  while(gpio_get_level(dir_pin_) != LOW)
  {
    // Wait for state change
  }

  return ret;      
}

unsigned long SerialPortHandler::getBaud() const
{
  return baud_;
}


