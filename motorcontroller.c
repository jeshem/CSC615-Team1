/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Shem Cheng
* Student ID: 920768313
* Github ID: Jeshem
* Project: Assignment 3 - Start Your Engines
* 
* File: motorcontroller.c
*
* Description: This file contains the method to set up wiringPi, wait for the button to be pressed, and run the motors
*
**************************************************************/

#include "motorcontroller.h"
#include <wiringPi.h>
#include <stdio.h>
#include <time.h>
#include <softPwm.h>


// Using Motor4 terminal
#define ENABLE 26 // pin 32 on motor shield
#define CONTROL1 10 // pin 24 on motor shield
#define CONTROL2 11 // pin 26 on motor shield
#define TRIGGER 0 // pin 11 on motor shield

#define LIGHT 24 // pin 33 on motor shield

#define HighSpeed 100
#define LowSpeed 0

void setupWiringPins() {
    wiringPiSetup();
    pinMode(ENABLE, OUTPUT);
    pinMode(CONTROL1, OUTPUT);
    pinMode(CONTROL2, OUTPUT);
    pinMode(TRIGGER, INPUT);
    pinMode(LIGHT, OUTPUT);
    
    softPwmCreate(ENABLE, LowSpeed, HighSpeed);
}

void waitForButton() {
    while (digitalRead(TRIGGER) != 1){
    }
    printf("Button pressed");
}

void runMotors() {
    printf("\nrunning motors\n");
    
    //start full power in one direction
    digitalWrite(LIGHT, HIGH);
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
}

void forward(){
    digitalWrite(CONTROL1, HIGH);
    digitalWrite(CONTROL2, LOW);
}

void reverse(){
    digitalWrite(CONTROL1, LOW);
    digitalWrite(CONTROL2, HIGH);
}

void accelerate(){
    int power;
    for(power=LowSpeed; power<HighSpeed; power+=10){
        softPwmWrite(ENABLE, power);
        printf("Speeding up\n");
        fflush(stdout);
        delay(200);
    }
}

void brake(){
    int power;
    for (power=HighSpeed; power>LowSpeed; power-=10) {
        softPwmWrite(ENABLE, power);
        printf("Slowing down\n");
        fflush(stdout);
        delay(200);
    }
}
