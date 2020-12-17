//
// Created by Justice, Bradley on 11/8/20.
//

#include <pthread.h>
#include "lineSensor.h"
#include <wiringPi.h>
#include <stdbool.h>
#include "motorcontroller.h"

void setupLineSensors() {

    //Line sensor pin setup
    pinMode(LeftLine, INPUT);
    pinMode(MiddleLine, INPUT);
    pinMode(RightLine, INPUT);
}

void setMiddleBaseLineReading(int read) {
    baseMiddleLineReading = read;
}

int getMiddleBaseLineReading() {
    return baseMiddleLineReading;
}

void setupInitialLineRead() {
    setMiddleBaseLineReading(digitalRead(MiddleLine));
    baseLeftLineReading = digitalRead(LeftLine);
    baseRightLineReading = digitalRead(RightLine);
}

void *readLine(void *threadid) {
    long tid = (long)threadid;
    stopMotors();
    while (true) {
        int line = digitalRead(MiddleLine);
        if (line == baseMiddleLineReading) {
            printf("Tracking Middle line\n");
            //forward(HalfSpeed);
        } else {
            //stopMotors();
            printf("Off the Middle line\n");
        }

        line = digitalRead(LeftLine);
        if (line != baseLeftLineReading) {
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

        line = digitalRead(RightLine);
        if (line != baseRightLineReading) {
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

        //delay(100);
    }
    pthread_exit(NULL);
}
