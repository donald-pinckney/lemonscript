//
//  auto_functions.c
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include "auto_functions.h"

#include <time.h>

bool DeployChokehold(void *data) {
    
    printf("BANG! Chokehold has been deployed!\n");
    
    // Code here to deploy mechanism
    
    return true;
    
}


int currentDistance = 0;
bool DriveStraight_3(void *data, float speed, int distance, bool left) {
    
    
    printf("DriveStraight_3: Driving kinda straight, with speed = %f, distance = %d, left = %d?\n", speed, distance, left);
    
    
    // Simulate driving here
    currentDistance += 10; // in.
    
    if(currentDistance > distance) {
        currentDistance = 0;
        return true;
    }
    
    return false;
}

bool DriveStraight_2(void *data, float speed, int distance) {
    
    printf("DriveStraight_2: Driving kinda straight, with speed = %f, distance = %d?\n", speed, distance);
    
    
    // Simulate driving here
    currentDistance += 10; // in.
    
    if(currentDistance > distance) {
        currentDistance = 0;
        return true;
    }
    
    return false;
}

bool DriveStraight_4(void *data, float speed, float distance) {
    
    printf("DriveStraight_4: Driving kinda straight, with speed = %f, distance = %f?\n", speed, distance);
    
    
    // Simulate driving here
    currentDistance += 10; // in.
    
    if(currentDistance > distance) {
        currentDistance = 0;
        return true;
    }
    
    return false;
}

bool CalibrateElevator(void *data) {
    printf("Calibrating elevator...\n");
    
    return true;
}

bool StopElevator(void *data) {
    printf("Elevator STOP\n");
    return true;
}
bool StopDriving(void *data) {
    printf("Driving STOP\n");
    return true;
}

bool RaiseWings(void *data) {
    printf("Raising wings\n");
    return true;
}

bool PointTurn(void *data, float x, float y, bool highgear) {
    printf("%f, %f, %d\n", x, y, highgear);
    return true;
}

bool TestBool(void *data, bool willPrintMe, bool otherBool) {
    printf("willPrintMe = %d, %d\n", willPrintMe, otherBool);
    return true;
}


double startTime = -1;
bool Wait(void *data, float t) {
    printf("Wait: %f\n", t);

    if(startTime < 0) {
        time_t timer;
        struct tm y2k = {0};
        
        y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
        y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
        
        time(&timer);  /* get current time; same as: timer = time(NULL)  */
        
        startTime = difftime(timer,mktime(&y2k));
        
        
    }
    
    
    time_t timer;
    struct tm y2k = {0};
    
    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
    
    time(&timer);  /* get current time; same as: timer = time(NULL)  */
    
    double currTime = difftime(timer,mktime(&y2k));
    
    
    if(currTime >= startTime + t) {
        startTime = -1;
        return true;
    }
    return false;
}
