/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef DYNAMIXEL_PORT_HANDLER_HPP_
#define DYNAMIXEL_PORT_HANDLER_HPP_

#include "driver/uart.h"
#include "driver/gpio.h"

#define GPIO_OUTPUT_PIN_SEL  (1ULL<<CONFIG_DXL_DIR_PIN)

class DXLPortHandler
{
  public:
    DXLPortHandler();
    
    virtual void begin() = 0;
    virtual void end() = 0;
    virtual int available(void) = 0;
    virtual int read() = 0;
    virtual size_t write(uint8_t) = 0;
    virtual size_t write(uint8_t *buf, size_t len) = 0;
    bool getOpenState();
    void setOpenState(bool);

  private:
    bool open_state_;
};


namespace DYNAMIXEL{

class SerialPortHandler : public DXLPortHandler
{
  public:
    SerialPortHandler(uart_port_t uart_num, gpio_num_t dir_pin);

    virtual void begin() override;
    virtual void end() override;
    virtual int available(void) override;
    virtual int read() override;
    virtual size_t write(uint8_t) override;
    virtual size_t write(uint8_t *buf, size_t len) override;

    virtual void begin(unsigned long baud);
    virtual unsigned long getBaud() const;

  private:
    uart_port_t uart_num_;
    const gpio_num_t dir_pin_;
    unsigned long baud_;
};

}//namespace DYNAMIXEL

#endif /* DYNAMIXEL_PORT_HANDLER_HPP_ */