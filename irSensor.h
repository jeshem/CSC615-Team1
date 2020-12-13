//
// Created by Justice, Bradley on 11/8/20.
//

#ifndef ASSIGNMENT5_IRSENSOR_H
#define ASSIGNMENT5_IRSENSOR_H

#define IR_READ 1
#include <wiringPi.h>
#include <stddef.h>
#include <stdio.h>

void setupIrSensors();

void *readIr(void *threadid);

#endif //ASSIGNMENT5_IRSENSOR_H
