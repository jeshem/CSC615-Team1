/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Bradley Justice
* Student ID: 920628173
* Github ID: pambalos
* Project: Assignment 1 - Traffic Light
*
* File: trafficlightwpi.h
*
* Description: a basic header file for holding the header details of the traffic light assignment with wiring pi.
*
**************************************************************/

#ifndef ASSIGNMENT_2_TAPELESS_RULER_PAMBALOS_ECHOSENSOR_H
#define ASSIGNMENT_2_TAPELESS_RULER_PAMBALOS_ECHOSENSOR_H

void setup();
void *readFrontDistance(void * tid);
void *readSideRearDistance(void * tid);

#endif //ASSIGNMENT_2_TAPELESS_RULER_PAMBALOS_ECHOSENSOR_H
