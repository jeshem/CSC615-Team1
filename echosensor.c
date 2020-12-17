/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Bradley Justice
* Student ID: 920628173
* Github ID: pambalos
* Project: Assignment 1 - Traffic Light
*
* File: echosensor.c
*
* Description: this contains the driver main as well as a runTrafficLight function for the wiringpi library traffic light.
*
**************************************************************/

#include "echosensor.h"
#include "motorcontroller.h"
#include <wiringPi.h>
#include <stdio.h>
#include <time.h>

#define TRIGGERFRONT 21
#define ECHOFRONT 22
#define TRIGGERREAR 9
#define ECHOREAR 7
#define VELOCITY_METERS_PER_SECOND 343

void *readSideRearDistance(void * tid) {
    time_t startTime, stopTime = 0;
    clock_t t0, t1 = 0, tt0, tt1 = 0;
    digitalWrite(TRIGGERREAR, LOW);
    delay(200);
    time(&startTime);
    digitalWrite(TRIGGERREAR, HIGH); delayMicroseconds(10); digitalWrite(TRIGGERREAR, LOW);
    do {
        tt0 = micros();
        time(&startTime);
        t0 = clock();
    } while (digitalRead(ECHOREAR) != 1);
    while (digitalRead(ECHOREAR) == 1) {
        time(&stopTime);
        t1 = clock() - t0;
        tt1 = micros();
    }
    double timeTaken = ((double)t1)/CLOCKS_PER_SEC;
    double timeTakenMicros = tt1 - tt0;
    double distanceByClock = ((VELOCITY_METERS_PER_SECOND*100)*(timeTaken))/2;
    double distanceByMicros = ((VELOCITY_METERS_PER_SECOND*100)*(timeTakenMicros/1000000))/2;
    printf("Rear side distanceByClock was: %fcm\n", distanceByClock);
    printf("Rear side distanceByMicros was: %fcm\n", distanceByMicros);
    fflush(stdout);
    if (distanceByClock < 30 || distanceByMicros < 30) {
        obstacleOnLeft = true;
    } else {
        obstacleOnLeft = false;
    }
    delay(300);
}
void *readFrontDistance(void * tid) {
    time_t startTime, stopTime = 0;
    clock_t t0, t1 = 0, tt0, tt1 = 0;
    digitalWrite(TRIGGERFRONT, LOW);
    delay(200);
    time(&startTime);
    digitalWrite(TRIGGERFRONT, HIGH); delayMicroseconds(10); digitalWrite(TRIGGERFRONT, LOW);
    do {
        tt0 = micros();
        time(&startTime);
        t0 = clock();
    } while (digitalRead(ECHOFRONT) != 1);
    while (digitalRead(ECHOFRONT) == 1) {
        time(&stopTime);
        t1 = clock() - t0;
        tt1 = micros();
    }
    double timeTaken = ((double)t1)/CLOCKS_PER_SEC;
    double timeTakenMicros = tt1 - tt0;
    double distanceByClock = ((VELOCITY_METERS_PER_SECOND*100)*(timeTaken))/2;
    double distanceByMicros = ((VELOCITY_METERS_PER_SECOND*100)*(timeTakenMicros/1000000))/2;
    printf("Front distanceByClock was: %fcm\n", distanceByClock);
    printf("Front distanceByMicros was: %fcm\n", distanceByMicros);
    fflush(stdout);
    if (distanceByClock < 30 || distanceByMicros < 30) {
        obstacleInFront = true;
    } else {
        obstacleInFront = false;
    }
    delay(300);
}

void setupEchoSensorPins() {
    pinMode(TRIGGERFRONT, OUTPUT);
    pinMode(ECHOFRONT, INPUT);
    pinMode(TRIGGERREAR, OUTPUT);
    pinMode(ECHOREAR, INPUT);
}
