//
// Created by Justice, Bradley on 11/8/20.
//

#ifndef ASSIGNMENT5_LINESENSOR_H

#define ASSIGNMENT5_LINESENSOR_H

#include <wiringPi.h>
#include <stddef.h>
#include <stdio.h>

void *readLine(void *threadid);

void setupLineSensors();
int getBaseLineReading();
void setBaseLineReading(int read);
void setupInitialLineRead();
int getLineReading(int sensor);
int baseLineReading;

#endif //ASSIGNMENT5_LINESENSOR_H
