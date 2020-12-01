/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Shem Cheng
* Student ID: 920768313
* Github ID: Jeshem
* Project: Assignment 3 - Start Your Engines
* 
* File: motorcontroller.c
*
* * Description: This file contains the method to set up wiringPi, wait for the button to be pressed, and run the motors
*
**************************************************************/

#include "motorcontroller.h"
#include <wiringPi.h>
#include <stdio.h>
#include <time.h>
#include <softPwm.h>

//Button Trigger for Motors
#define TRIGGER 7 // pin 7 on motor shield

// Motor 1 Terminal
#define ENABLE1 0 // pin 11 on motor shield
#define MOTOR1CONTROL1 2 // pin 13 on motor shield
#define MOTOR1CONTROL2 3 // pin 15 on motor shield

// Motor 2 Terminal
#define ENABLE2 6 // pin 22 on motor shield
#define MOTOR2CONTROL1 4 // pin 16 on motor shield
#define MOTOR2CONTROL2 5 // pin 18 on motor shield

// Motor 3 Terminal
#define ENABLE3 12 // pin 19 on motor shield
#define MOTOR3CONTROL1 13 // pin 21 on motor shield
#define MOTOR3CONTROL2 14 // pin 23 on motor shield

// Motor 4 Terminal
#define ENABLE4 26 // pin 32 on motor shield
#define MOTOR4CONTROL1 10 // pin 24 on motor shield
#define MOTOR4CONTROL2 11 // pin 26 on motor shield

#define LIGHT 24 // pin 33 on motor shield

#define HighSpeed 100
#define LowSpeed 15

void setupWiringPins() {
    wiringPiSetup();
    
    softPwmCreate(ENABLE1, 100, 100);
    softPwmCreate(MOTOR1CONTROL1, 1, 100);
    softPwmCreate(MOTOR1CONTROL2, 1, 100);

    softPwmCreate(ENABLE2, 100, 100);
    softPwmCreate(MOTOR2CONTROL1, 1, 100);
    softPwmCreate(MOTOR2CONTROL2, 1, 100);

    softPwmCreate(ENABLE3, 100, 100);
    softPwmCreate(MOTOR3CONTROL1, 1, 100);
    softPwmCreate(MOTOR3CONTROL2, 1, 100);

    softPwmCreate(ENABLE4, 100, 100);
    softPwmCreate(MOTOR4CONTROL1, 1, 100);
    softPwmCreate(MOTOR4CONTROL2, 1, 100);
    
    pinMode(TRIGGER, INPUT);
    pinMode(LIGHT, OUTPUT);
    
    digitalWrite(TRIGGER, LOW);
    
    delay(10);
}

void waitForButton() {
    while (digitalRead(TRIGGER) != 1){
    }
    printf("Button pressed");
}

void runMotors() {
    printf("\nrunning motors\n");
    
    //accelerate to full power in one direction
    digitalWrite(LIGHT, HIGH);
    digitalWrite(ENABLE1, HIGH);
    digitalWrite(ENABLE2, HIGH);
    digitalWrite(ENABLE3, HIGH);
    digitalWrite(ENABLE4, HIGH);
    forward();
    accelerate();
    
    
    //slow down over time to a stop
    brake();
    digitalWrite(LIGHT, LOW);
    

    //run in reverse direction
    digitalWrite(LIGHT, HIGH);
    reverse();
    accelerate();
    
    //slow down again over time to a stop
    brake();
    digitalWrite(LIGHT, LOW);
    
    //stop all motors
    softPwmWrite(ENABLE1, 0);
    softPwmWrite(ENABLE2, 0);
    softPwmWrite(ENABLE3, 0);
    softPwmWrite(ENABLE4, 0);
}

void forward(){

    //Motor 1 Forward
    softPwmWrite(MOTOR1CONTROL1, 100);
    softPwmWrite(MOTOR1CONTROL2, 0);

    //Motor 2 Forward
    softPwmWrite(MOTOR2CONTROL1, 100);
    softPwmWrite(MOTOR2CONTROL2, 0);

    //Motor 3 Forward
    softPwmWrite(MOTOR3CONTROL1, 100);
    softPwmWrite(MOTOR3CONTROL2, 0);

    //Motor 4 Forward
    softPwmWrite(MOTOR4CONTROL1, 100);
    softPwmWrite(MOTOR4CONTROL2, 0);
}

void reverse(){
    //Motor 1 Reverse
    softPwmWrite(MOTOR1CONTROL1, 0);
    softPwmWrite(MOTOR1CONTROL2, 100);

    //Motor 2 Reverse
    softPwmWrite(MOTOR2CONTROL1, 0);
    softPwmWrite(MOTOR2CONTROL2, 100);

    //Motor 3 Reverse
    softPwmWrite(MOTOR3CONTROL1, 0);
    softPwmWrite(MOTOR3CONTROL2, 100);

    //Motor 4 Reverse
    softPwmWrite(MOTOR4CONTROL1, 0);
    softPwmWrite(MOTOR4CONTROL2, 100);
}

void accelerate(){
    int power;
    for(power=LowSpeed; power<HighSpeed; power+=10){
        softPwmWrite(ENABLE1, power);
        softPwmWrite(ENABLE2, power);
        softPwmWrite(ENABLE3, power);
        softPwmWrite(ENABLE4, power);
        printf("Speeding up\n");
        fflush(stdout);
        delay(200);
    }
    delay(2000);
}

void brake(){
    int power;
    for (power=HighSpeed; power>LowSpeed; power-=10) {
        softPwmWrite(ENABLE1, power);
        softPwmWrite(ENABLE2, power);
        softPwmWrite(ENABLE3, power);
        softPwmWrite(ENABLE4, power);
        printf("Slowing down\n");
        fflush(stdout);
        delay(200);
    }
    delay(1000);
}
