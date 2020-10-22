/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Shem Cheng
* Student ID: 920768313
* Github ID: Jeshem
* Project: Assignment 3 - Start Your Engines
*
* File: motorcontroller.h
*
* Description: a basic header file for holding the header details of the motor assignment with wiringPi and softPWM.
*
**************************************************************/

#include <stdbool.h>

void setupWiringPins();
void runMotors();
void waitForButton();
void forward();
void reverse();
void accelerate();
void brake();
