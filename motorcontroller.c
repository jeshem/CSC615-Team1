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
#include "lineSensor.h"
#include <wiringPi.h>
#include <stdio.h>
#include <time.h>
#include <softPwm.h>
#include <stdatomic.h>

//Button Trigger for Motors
#define TRIGGER 7 // pin 7 on motor shield

// Motor 1 Terminal - front left
#define FRONTLEFT 0 // pin 11 on motor shield
#define FRONTLEFTCONTROL1 2 // pin 13 on motor shield
#define FRONTLEFTCONTROL2 3 // pin 15 on motor shield

// Motor 2 Terminal - rear left
#define REARLEFT 6 // pin 22 on motor shield
#define REARLEFTCONTROL1 4 // pin 16 on motor shield
#define REARLEFTCONTROL2 5 // pin 18 on motor shield

// Motor 3 Terminal - rear right
#define REARRIGHT 12 // pin 19 on motor shield
#define REARRIGHTCONTROL1 13 // pin 21 on motor shield
#define REARRIGHTCONTROL2 14 // pin 23 on motor shield

// Motor 4 Terminal - front right
#define FRONTRIGHT 26 // pin 32 on motor shield
#define FRONTRIGHTCONTROL1 10 // pin 24 on motor shield
#define FRONTRIGHTCONTROL2 11 // pin 26 on motor shield

#define LIGHT 24 // pin 33 on motor shield

void runMotors() {
    while (true) {
        //do nothing for now, later check for control flags
        if (middleLineOn) {
            printf("Tracking Middle line\n");
            forward(OneSpeed);
        } else if (leftLineOn) {
            printf("Should be rotating left\n");
            while (digitalRead(MiddleLine) != baseMiddleLineReading) {
                rotateLeft();
            }
            leftLineOn = false;
            middleLineOn = true;
            forward(OneSpeed);
        } else if (rightLineOn) {
            printf("Should be rotating right\n");
            while (digitalRead(MiddleLine) != baseMiddleLineReading) {
                rotateRight();
            }
            rightLineOn = false;
            middleLineOn = true;
            forward(OneSpeed);
        } else if (!rightLineOn && !leftLineOn && !middleLineOn) {
            printf("should be moving forward at low speed\n");
            forward(OneSpeed);
        }
    }
}

void testMotors() {
    brake();
    printf("Should be running front left\n");
    //Motor 1 Forward
    digitalWrite(FRONTLEFT, HIGH);
    softPwmWrite(FRONTLEFTCONTROL1, OneSpeed);
    softPwmWrite(FRONTLEFTCONTROL2, 0);
    delay(4000); brake();

    printf("Should be running rear left\n");
    //Motor 2 Forward
    digitalWrite(REARLEFT, HIGH);
    softPwmWrite(REARLEFTCONTROL1, OneSpeed);
    softPwmWrite(REARLEFTCONTROL2, 0);
    delay(4000); brake();

    printf("Should be running rear right\n");
    //Motor 3 Forward
    digitalWrite(REARRIGHT, HIGH);
    softPwmWrite(REARRIGHTCONTROL1, OneSpeed);
    softPwmWrite(REARRIGHTCONTROL2, 0);
    delay(4000); brake();

    printf("Should be running front right\n");
    //Motor 4 Forward
    digitalWrite(FRONTRIGHT, HIGH);
    softPwmWrite(FRONTRIGHTCONTROL1, OneSpeed);
    softPwmWrite(FRONTRIGHTCONTROL2, 0);
    delay(4000); brake();
}

void setupMotors() {

    enableMotors();
    softPwmCreate(FRONTLEFT, 100, 100);
    softPwmCreate(FRONTLEFTCONTROL1, 1, 100);
    softPwmCreate(FRONTLEFTCONTROL2, 1, 100);

    softPwmCreate(REARLEFT, 100, 100);
    softPwmCreate(REARLEFTCONTROL1, 1, 100);
    softPwmCreate(REARLEFTCONTROL2, 1, 100);

    softPwmCreate(REARRIGHT, 100, 100);
    softPwmCreate(REARRIGHTCONTROL1, 1, 100);
    softPwmCreate(REARRIGHTCONTROL2, 1, 100);

    softPwmCreate(FRONTRIGHT, 100, 100);
    softPwmCreate(FRONTRIGHTCONTROL1, 1, 100);
    softPwmCreate(FRONTRIGHTCONTROL2, 1, 100);
    
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

void stopMotors() {
    //stop all motors
    disableMotors();
    softPwmWrite(FRONTLEFT, 0);
    softPwmWrite(REARLEFT, 0);
    softPwmWrite(REARRIGHT, 0);
    softPwmWrite(FRONTRIGHT, 0);
}

void forward(int speed){
    enableMotors();

    //Motor 1 Forward
    softPwmWrite(FRONTLEFTCONTROL1, speed);
    softPwmWrite(FRONTLEFTCONTROL2, 0);

    //Motor 2 Forward
    softPwmWrite(REARLEFTCONTROL1, speed);
    softPwmWrite(REARLEFTCONTROL2, 0);

    //Motor 3 Forward
    softPwmWrite(REARRIGHTCONTROL1, speed);
    softPwmWrite(REARRIGHTCONTROL2, 0);

    //Motor 4 Forward
    softPwmWrite(FRONTRIGHTCONTROL1, speed);
    softPwmWrite(FRONTRIGHTCONTROL2, 0);
}

void rotateRight() {
    //right side motors go reverse OneSpeed

    enableMotors();
    softPwmWrite(FRONTRIGHTCONTROL1, 0);
    softPwmWrite(FRONTRIGHTCONTROL2, OneSpeed);

    softPwmWrite(REARRIGHTCONTROL1, 0);
    softPwmWrite(REARRIGHTCONTROL2, OneSpeed);

    //left side motors go forward OneSpeed
    softPwmWrite(FRONTLEFTCONTROL1, OneSpeed);
    softPwmWrite(FRONTLEFTCONTROL2, 0);

    softPwmWrite(REARLEFTCONTROL1, OneSpeed);
    softPwmWrite(REARLEFTCONTROL2, 0);
}

void enableMotors() {
    digitalWrite(FRONTLEFT, HIGH);
    digitalWrite(REARLEFT, HIGH);
    digitalWrite(REARRIGHT, HIGH);
    digitalWrite(FRONTRIGHT, HIGH);
}

void disableMotors() {
    digitalWrite(FRONTLEFT, LOW);
    digitalWrite(REARLEFT, LOW);
    digitalWrite(REARRIGHT, LOW);
    digitalWrite(FRONTRIGHT, LOW);
}

void rotateLeft() {
    //right side motors go reverse OneSpeed

    enableMotors();
    softPwmWrite(FRONTRIGHTCONTROL1, OneSpeed);
    softPwmWrite(FRONTRIGHTCONTROL2, 0);

    softPwmWrite(REARRIGHTCONTROL1, OneSpeed);
    softPwmWrite(REARRIGHTCONTROL2, 0);

    //left side motors go forward OneSpeed
    softPwmWrite(FRONTLEFTCONTROL1, 0);
    softPwmWrite(FRONTLEFTCONTROL2, OneSpeed);

    softPwmWrite(REARLEFTCONTROL1, 0);
    softPwmWrite(REARLEFTCONTROL2, OneSpeed);
}

void reverse(){
    //Motor 1 Reverse
    softPwmWrite(FRONTLEFTCONTROL1, 0);
    softPwmWrite(FRONTLEFTCONTROL2, 100);

    //Motor 2 Reverse
    softPwmWrite(REARLEFTCONTROL1, 0);
    softPwmWrite(REARLEFTCONTROL2, 100);

    //Motor 3 Reverse
    softPwmWrite(REARRIGHTCONTROL1, 0);
    softPwmWrite(REARRIGHTCONTROL2, 100);

    //Motor 4 Reverse
    softPwmWrite(FRONTRIGHTCONTROL1, 0);
    softPwmWrite(FRONTRIGHTCONTROL2, 100);
}

void accelerate(){
    int power;
    for(power=LowSpeed; power<HighSpeed; power+=10){
        if (power > 100) power = 100;
        softPwmWrite(FRONTLEFT, power);
        softPwmWrite(REARLEFT, power);
        softPwmWrite(REARRIGHT, power);
        softPwmWrite(FRONTRIGHT, power);
        printf("Speeding up\n");
        fflush(stdout);
        delay(200);
    }
    delay(2000);
}

void brake(){
    int power;
    disableMotors();
    /*
    for (power=HighSpeed; power>LowSpeed; power-=10) {
        softPwmWrite(FRONTLEFT, 0);
        softPwmWrite(REARLEFT, 0);
        softPwmWrite(REARRIGHT, 0);
        softPwmWrite(FRONTRIGHT, 0);
        printf("Slowing down\n");
        fflush(stdout);
        delay(200);
    }
     */
    delay(1000);
}
