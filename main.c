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
#include "motorcontroller.h"


int main(int argc, char *argv[]) {
    setupWiringPins();
    waitForButton();
    runMotors();
    return 0;
}

