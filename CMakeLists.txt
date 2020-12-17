cmake_minimum_required(VERSION 3.15)
project(assignment5 C)

set(CMAKE_C_STANDARD 99)

add_executable(driver main.c lineSensor.h irSensor.h motorcontroller.h motorcontroller.c irSensor.c lineSensor.c)