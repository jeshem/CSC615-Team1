//
// Created by Justice, Bradley on 11/8/20.
//

#include <pthread.h>
#include "lineSensor.h"
#include <wiringPi.h>
#include <stdbool.h>
#include "motorcontroller.h"

// Line Sensors
#define LeftmostLine 15 //pin #10
#define LeftLine 14 //pin #8
#define MiddleLine 4 //pin #7
#define RightLine 3 //pin #5
#define RightmostLine 2 //pin #3

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

void setupLineSensors() {

    //Line sensor pin setup
    pinMode(LeftmostLine, INPUT);
    pinMode(LeftLine, INPUT);
    pinMode(MiddleLine, INPUT);
    pinMode(RightLine, INPUT);
    pinMode(RightmostLine, INPUT);
}

void *readLine(void *threadid) {
    long tid = (long)threadid;
    stopMotors();
    while (true) {
        int line = digitalRead(MiddleLine);
        if (line == 1) {
            printf("Tracking Middle line\n");
            //forward(HalfSpeed);
        } else {
            //stopMotors();
            printf("Off the Middle line\n");
        }

        line = digitalRead(LeftLine);
        if (line == 1) {
            printf("LeftLine detected! Angle Left\n");
            /*
            while (digitalRead(MiddleLine) != 1) {
                rotateLeft();
            }
            stopMotors();
             */
        } else {
            //printf("Off the line\n");
        }

        line = digitalRead(LeftmostLine);
        if (line == 1) {
            printf("LeftMostLine detected! Big Left (Rotate maybe?)\n");
            /*
            while (digitalRead(MiddleLine) != 1) {
                rotateLeft();
            }
            stopMotors();
            */
        } else {
            //printf("Off the line\n");
        }

        line = digitalRead(RightLine);
        if (line == 1) {
            printf("RightLine detected! Angle Right\n");
            /*
            while (digitalRead(MiddleLine) != 1) {
                rotateRight();
            }
             */
            stopMotors();
        } else {
            //printf("Off the line\n");
        }

        line = digitalRead(RightmostLine);
        if (line == 1) {
            printf("RightmostLine detected! Big Right (Rotate maybe?)\n");
            /*
            while (digitalRead(MiddleLine) != 1) {
                rotateRight();
            }
             */
            stopMotors();
        } else {
            //printf("Off the line\n");
        }
        //delay(100);
    }
    pthread_exit(NULL);
}