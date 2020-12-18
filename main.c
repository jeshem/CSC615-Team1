/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Shem Cheng
* Student ID: 920768313
* Github ID: Jeshem
* Project: Assignment 3 - Start Your Engines
* 
* File: main.c
*
* Description: this file contains the main method that calls the other methods
**************************************************************/

#include <wiringPi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>
#include <softPwm.h>
#include <pthread.h>
#include "motorcontroller.h"
#include "lineSensor.h"
#include "irSensor.h"
#include "echosensor.h"

void setup();
void setupLineSensorThreads();
void setupIrSensorThreads();
void setupEchoSensorThreads();

void testRotate();

int main(int argc, char *argv[]) {
    setup();
    delay(2000);
    printf("Now executing normal code");
    //setupLineSensorThreads();
    //setupIrSensorThreads();
    //waitForButton();
    //runMotors();
    enableMotors();
    while (true) {
        //testRotate();

        int line = digitalRead(MiddleLine);
        if (line == baseMiddleLineReading) {
            printf("Tracking Middle line\n");
            middleLineOn = true;
            rotatingLeft = false;
            rotatingRight = false;
            forward(OneSpeed);
            //delay(500);
        } else {
            //stopMotors();
            middleLineOn = false;
            printf("Off the Middle line\n");

            line = digitalRead(LeftLine);
            if (line != baseLeftLineReading) {
                printf("LeftLine detected! Angle Left\n");
                leftLineOn = true;
                while (digitalRead(MiddleLine) != baseMiddleLineReading) {
                    rotateLeft();
                }
                //stopMotors();
            } else {
                forward(OneSpeed);
                leftLineOn = false;
                printf("Off the line\n");
            }

            line = digitalRead(RightLine);
            if (line != baseRightLineReading) {
                rightLineOn = true;
                printf("RightLine detected! Angle Right\n");
                while (digitalRead(MiddleLine) != baseMiddleLineReading) {
                    rotateRight();
                }
                //stopMotors();
            } else {
                rightLineOn = false;
                forward(OneSpeed);
                printf("Off the line\n");
            }
        }
        //delay(100);
    }
    return 0;
}

void testRotate() {
    printf("Rotating right\n");
    rotateRight();
    delay(6000);
    brake();
    printf("Rotating left\n");
    rotateLeft();
    delay(6000);
}

/**
 * Setup wiringpi required setup as well as setting the pin modes for motors, ir sensors and line sensors.
 */
void setup() {
    wiringPiSetup();
    setupEchoSensorPins();
    setupMotors();
    setupIrSensors();
    setupLineSensors();
    setupInitialLineRead(); //reads the current middle line and sets the baseline as either 1 or 0
    setupEchoSensorThreads();
}

void setupEchoSensorThreads() {
    pthread_t t1, t2;
    int creationError, i, i2;
    creationError = pthread_create(&t1, NULL, readFrontDistance, (void *)i);
    if (creationError) {
        printf("Error:unable to create echo sensor thread \n");
    }
    creationError = pthread_create(&t2, NULL, readSideRearDistance, (void *)i2);
    if (creationError) {
        printf("Error:unable to create echo sensor thread \n");
    }
}

void setupLineSensorThreads() {
    pthread_t t1;
    int creationError, i;
    creationError = pthread_create(&t1, NULL, readLine, (void *)i);
    if (creationError) {
        printf("Error:unable to create Line thread \n");
    }
}

void setupIrSensorThreads() {
    pthread_t t2;
    int creationError, i;
    creationError = pthread_create(&t2, NULL, readIr, (void *)i);
    if (creationError) {
        printf("Error:unable to create IR thread \n");
    }
}
