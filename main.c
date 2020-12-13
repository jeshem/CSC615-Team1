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

// Line Sensors
#define LeftmostLine 15 //pin #10
#define LeftLine 14 //pin #8
#define MiddleLine 4 //pin #7
#define RightLine 3 //pin #5
#define RightmostLine 2 //pin #3

void setup();
void setupLineSensorThreads();
void setupIrSensorThreads();

int main(int argc, char *argv[]) {
    setup();
    setupLineSensorThreads();
    setupIrSensorThreads();
    //waitForButton();
    //runMotors();

    return 0;
}

/**
 * Setup wiringpi required setup as well as setting the pin modes for motors, ir sensors and line sensors.
 */
void setup() {
    wiringPiSetup();
    setupMotors();
    setupIrSensors();
    setupLineSensors();
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
    pthread_t t1;
    int creationError, i;
    creationError = pthread_create(&t1, NULL, readIr, (void *)i);
    if (creationError) {
        printf("Error:unable to create Line thread \n");
    }
}