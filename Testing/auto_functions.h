//
//  auto_functions.h
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef auto_functions_h
#define auto_functions_h

#include <stdio.h>

bool DeployChokehold();
bool DriveStraight_2(float speed, int distance);
bool DriveStraight_4(float speed, float distance);
bool DriveStraight_3(float speed, int distance, bool left);

bool CalibrateElevator();
bool StopElevator();
bool StopDriving();
bool RaiseWings();

#endif /* auto_functions_h */
