//
//  auto_functions.c
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include "auto_functions.h"

bool DeployChokehold() {
    
    printf("BANG! Chokehold has been deployed!\n");
    
    // Code here to deploy mechanism
    
    return true;
    
}


int currentDistance = 0;
bool DriveStraight_3(float speed, int distance, bool left) {
    
    
    printf("DriveStraight_3: Driving kinda straight, with speed = %f, distance = %d, left = %d?\n", speed, distance, left);
    
    
    // Simulate driving here
    currentDistance += 10; // in.
    
    if(currentDistance > distance) {
        return true;
    }
    
    return false;
}

bool DriveStraight_2(float speed, int distance) {
    
    printf("DriveStraight_2: Driving kinda straight, with speed = %f, distance = %d?\n", speed, distance);
    
    
    // Simulate driving here
    currentDistance += 10; // in.
    
    if(currentDistance > distance) {
        return true;
    }
    
    return false;
}