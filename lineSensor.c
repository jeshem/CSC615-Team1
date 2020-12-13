//
// Created by Justice, Bradley on 11/8/20.
//

#include <pthread.h>
#include "lineSensor.h"
#include <wiringPi.h>
#include <stdbool.h>

// Line Sensors
#define LeftmostLine 15 //pin #10
#define LeftLine 14 //pin #8
#define MiddleLine 4 //pin #7
#define RightLine 3 //pin #5
#define RightmostLine 2 //pin #3

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
    while (true) {
        int line = digitalRead(MiddleLine);
        if (line == 1) {
            printf("Tracking Middle line\n");
        } else {
            printf("Off the Middle line\n");
        }

        line = digitalRead(LeftLine);
        if (line == 1) {
            printf("LeftLine detected! Angle Left\n");
        } else {
            //printf("Off the line\n");
        }

        line = digitalRead(LeftmostLine);
        if (line == 1) {
            printf("LeftMostLine detected! Big Left (Rotate maybe?)\n");
        } else {
            printf("On the line\n");
        }

        line = digitalRead(RightLine);
        if (line == 1) {
            printf("RightLine detected! Angle Right\n");
        } else {
            //printf("Off the line\n");
        }

        line = digitalRead(RightmostLine);
        if (line == 1) {
            printf("RightmostLine detected! Big Right (Rotate maybe?)\n");
        } else {
            //printf("Off the line\n");
        }
        delay(100);
    }
    pthread_exit(NULL);
}