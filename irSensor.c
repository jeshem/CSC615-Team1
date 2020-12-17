//
// Created by Justice, Bradley on 11/8/20.
//

#include "irSensor.h"
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

//IR sensors
#define FrontIR 21 //pin #40
#define FrontSidewaysIR 20 //pin #38
#define RearIR 26 //pin #37
#define RearSidewaysIR 19 //pin #35

void setupIrSensors() {

    //IR sensor pin setup
    pinMode(FrontIR, INPUT);
    pinMode(FrontSidewaysIR, INPUT);
    pinMode(RearIR, INPUT);
    pinMode(RearSidewaysIR, INPUT);
}

void *readIr(void *threadid) {
    long tid = (long)threadid;
    while (true) {
        int ir = digitalRead(FrontIR);
        if (ir != 1) {
            printf("Something is in front of the Car\n");
        }
        ir = digitalRead(FrontSidewaysIR);
        if (ir != 1) {
            printf("Something is to the left of the front of theCar\n");
        }
        ir = digitalRead(RearIR);
        if (ir != 1) {
            printf("Something is behind the Car\n");
        }
        ir = digitalRead(RearSidewaysIR);
        if (ir != 1) {
            printf("Something is to the left of the back of the Car\n");
        }
        //delay(1000);
    }
    pthread_exit(NULL);
}