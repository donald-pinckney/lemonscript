//
//  PlayTestsShared.cpp
//  lemonscript
//
//  Created by Donald Pinckney on 5/23/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include "PlayTestsShared.h"

#include <lemonscript/lemonscript.h>
#include <lemonscript/AvailableCppCommandDeclaration.h>
#include <lemonscript/LemonScriptState.h>


#include "auto_functions.h"

using namespace lemonscript;

LemonScriptState * PlayTestsShared::play_tests_make_state() {
    AvailableCppCommandDeclaration *driveStraight3 = new AvailableCppCommandDeclaration((void *)DriveStraight_3, "DriveStraight", {DataType::FLOAT, DataType::INT, DataType::BOOLEAN});
    AvailableCppCommandDeclaration *driveStraight2 = new AvailableCppCommandDeclaration((void *)DriveStraight_2, "DriveStraight", {DataType::FLOAT, DataType::INT});
    AvailableCppCommandDeclaration *driveStraight4 = new AvailableCppCommandDeclaration((void *)DriveStraight_4, "DriveStraight", {DataType::FLOAT, DataType::FLOAT});
    AvailableCppCommandDeclaration *deployChokehold = new AvailableCppCommandDeclaration((void *)DeployChokehold, "DeployChokehold", {});
    AvailableCppCommandDeclaration *calibrateElevator = new AvailableCppCommandDeclaration((void *)CalibrateElevator, "CalibrateElevator", {});
    AvailableCppCommandDeclaration *stopElevator = new AvailableCppCommandDeclaration((void *)StopElevator, "StopElevator", {});
    AvailableCppCommandDeclaration *stopDriving = new AvailableCppCommandDeclaration((void *)StopDriving, "StopDriving", {});
    AvailableCppCommandDeclaration *raiseWings = new AvailableCppCommandDeclaration((void *)RaiseWings, "RaiseWings", {});
    AvailableCppCommandDeclaration *pointTurn = new AvailableCppCommandDeclaration((void *)PointTurn, "PointTurn", {DataType::FLOAT, DataType::FLOAT, DataType::BOOLEAN});
    AvailableCppCommandDeclaration *pointTurn2 = new AvailableCppCommandDeclaration((void *)PointTurn2, "PointTurn", {DataType::FLOAT});
    
    AvailableCppCommandDeclaration *wait = new AvailableCppCommandDeclaration((void *)Wait, "Wait", {DataType::INT});
    AvailableCppCommandDeclaration *wait5 = new AvailableCppCommandDeclaration((void *)Wait5, "Wait5", {});
    
    AvailableCppCommandDeclaration *testBool = new AvailableCppCommandDeclaration((void *)TestBool, "TestBool", {DataType::BOOLEAN, DataType::BOOLEAN});
    AvailableCppCommandDeclaration *printF = new AvailableCppCommandDeclaration((void *)PrintF, "Print", {DataType::FLOAT});
    AvailableCppCommandDeclaration *printI = new AvailableCppCommandDeclaration((void *)PrintI, "Print", {DataType::INT});
    AvailableCppCommandDeclaration *printB = new AvailableCppCommandDeclaration((void *)PrintB, "Print", {DataType::BOOLEAN});
    
    
    
    std::vector<const AvailableCppCommandDeclaration *> commands = {driveStraight3, driveStraight2, driveStraight4, deployChokehold, calibrateElevator, stopElevator, stopDriving, raiseWings, pointTurn, pointTurn2, wait, wait5, testBool, printF, printI, printB};
    
    LemonScriptState *state = new LemonScriptState();
    state->declareAvailableCppCommands(commands);
    
    return state;
}