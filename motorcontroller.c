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
        /*if (obstacleInFront) {
            brake();
            printf("Obstacle in front... braking.\n");
        } else*/
        if (middleLineOn) {
            printf("Tracking Middle line\n");
            forward(OneSpeed);
            rotatingRight = false;
            rotatingLeft = false;
            delay(1000);
        }/*
        else if (leftLineOn) {
            printf("Should be rotating left\n");
            rotatingLeft = true;
            while (digitalRead(MiddleLine) != baseMiddleLineReading) {
                rotateLeft();
            }
            rotatingLeft = false;
            leftLineOn = false;
            middleLineOn = true;
            forward(OneSpeed);
            printf("Should be moving forward\n");
            delay(500);
        } else if (rightLineOn) {
            printf("Should be rotating right\n");
            rotatingRight = true;
            while (digitalRead(MiddleLine) != baseMiddleLineReading) {
                rotateRight();
            }
            rotatingRight = false;
            rightLineOn = false;
            middleLineOn = true;
            printf("Should be moving forward\n");
            forward(OneSpeed);
            delay(500);
        } else if (!rightLineOn && !leftLineOn && !middleLineOn) {
            printf("should be moving forward at low speed\n");
            forward(OneSpeed);
        } else {
            printf("No sensors activated should move forward...\n");
            forward(OneSpeed);
        }
        */
        delay(50);
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
    rotatingLeft = false;
    rotatingRight = false;
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

    avoidingObstacle = false;
    obstacleInFront = false;
    obstacleOnLeft = false;
    obstacleClearedBack = false;
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
    //enableMotors();
    rotatingRight = false; rotatingRight = false;
    printf("Should be running forward\n");

    //Motor 1 Forward
    //softPwmCreate(FRONTLEFT, speed, speed);
    digitalWrite(FRONTLEFT, HIGH);
    softPwmWrite(FRONTLEFTCONTROL1, speed+10);
    softPwmWrite(FRONTLEFTCONTROL2, 0);

    //Motor 2 Forward
    //softPwmCreate(REARLEFT, speed, speed);
    digitalWrite(REARLEFT, HIGH);
    softPwmWrite(REARLEFTCONTROL1, speed+10);
    softPwmWrite(REARLEFTCONTROL2, 0);

    //Motor 3 Forward
    //softPwmCreate(REARRIGHT, speed, speed);
    digitalWrite(REARRIGHT, HIGH);
    softPwmWrite(REARRIGHTCONTROL1, speed);
    softPwmWrite(REARRIGHTCONTROL2, 0);

    //Motor 4 Forward
    //softPwmCreate(FRONTRIGHT, speed, speed);
    digitalWrite(FRONTRIGHT, HIGH);
    softPwmWrite(FRONTRIGHTCONTROL1, speed);
    softPwmWrite(FRONTRIGHTCONTROL2, 0);

    //delay(2000);
}

void rotateRight() {
    //right side motors go reverse OneSpeed

    //enableMotors();
    softPwmWrite(FRONTRIGHTCONTROL1, 0);
    softPwmWrite(FRONTRIGHTCONTROL2, 0);

    softPwmWrite(REARRIGHTCONTROL1, 0);
    softPwmWrite(REARRIGHTCONTROL2, 0);

    //left side motors go forward OneSpeed
    softPwmWrite(FRONTLEFTCONTROL1, ThreeSpeed);
    softPwmWrite(FRONTLEFTCONTROL2, 0);

    softPwmWrite(REARLEFTCONTROL1, ThreeSpeed);
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

    //enableMotors();
    softPwmWrite(FRONTRIGHTCONTROL1, ThreeSpeed);
    softPwmWrite(FRONTRIGHTCONTROL2, 0);

    softPwmWrite(REARRIGHTCONTROL1, ThreeSpeed);
    softPwmWrite(REARRIGHTCONTROL2, 0);

    //left side motors go forward OneSpeed
    softPwmWrite(FRONTLEFTCONTROL1, 0);
    softPwmWrite(FRONTLEFTCONTROL2, 0);

    softPwmWrite(REARLEFTCONTROL1, 0);
    softPwmWrite(REARLEFTCONTROL2, 0);
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
    for(power=LowSpeed; power<OneSpeed; power+=10){
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
    for (power=OneSpeed; power>LowSpeed; power-=10) {
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
