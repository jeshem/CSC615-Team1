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

void setupMotors();
void runMotors();
void waitForButton();
void forward(int speed);
void rotateRight();
void rotateLeft();
void stopMotors();
void reverse();
void accelerate();
void brake();
void testMotors();

#define HIGH 1
#define LOW 0

// Line Sensors
//#define LeftmostLine 15 //pin #10
#define LeftLine 29 //pin #40
#define MiddleLine 28 //pin #38
#define RightLine 27 //pin #36
//#define RightmostLine 2 //pin #3

//Speed settings
#define HighSpeed 100
#define ThreeSpeed 75
#define HalfSpeed 50
#define OneSpeed 25
#define LowSpeed 15

//Motors
#define FRONTLEFT 0 // pin 11 on motor shield
#define REARLEFT 6 // pin 22 on motor shield
#define REARRIGHT 12 // pin 19 on motor shield
#define FRONTRIGHT 26 // pin 32 on motor shield


//Speed settings
#define HighSpeed 100
#define ThreeSpeed 75
#define HalfSpeed 50
#define OneSpeed 25
#define LowSpeed 15

bool middleLineOn;
bool leftLineOn;
bool rightLineOn;
