cmake_minimum_required(VERSION 3.24)

idf_component_register(
SRCS 
    "actuator.cpp"
    "arduino_droppings.cpp"
    "dynamixel2espressif.cpp"
    "master.cpp"
    "port_handler.cpp"
    "protocol.cpp"
INCLUDE_DIRS 
    "." 
    "./include"
REQUIRES 
    driver
)
