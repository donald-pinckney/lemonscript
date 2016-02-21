//
//  mainLemonScript.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

#include "CppCommand.h"
#include "SequentialCommand.h"
#include "SimultaneousCommand.h"
#include "auto_functions.h"
#include "LemonScriptTokenizer.h"
#include "LemonScriptCompiler.h"

#include "ParsingUtils.h"

int main() {
        
    
    
    try {        
        
        lemonscript::AvailableCppCommandDeclaration *driveStraight3 = new lemonscript::AvailableCppCommandDeclaration((void *)DriveStraight_3, "DriveStraight", {FLOAT, INT, BOOLEAN});
        lemonscript::AvailableCppCommandDeclaration *driveStraight2 = new lemonscript::AvailableCppCommandDeclaration((void *)DriveStraight_2, "DriveStraight", {FLOAT, INT});
        lemonscript::AvailableCppCommandDeclaration *driveStraight4 = new lemonscript::AvailableCppCommandDeclaration((void *)DriveStraight_4, "DriveStraight", {FLOAT, FLOAT});
        lemonscript::AvailableCppCommandDeclaration *deployChokehold = new lemonscript::AvailableCppCommandDeclaration((void *)DeployChokehold, "DeployChokehold", {});
        lemonscript::AvailableCppCommandDeclaration *calibrateElevator = new lemonscript::AvailableCppCommandDeclaration((void *)CalibrateElevator, "CalibrateElevator", {});
        lemonscript::AvailableCppCommandDeclaration *stopElevator = new lemonscript::AvailableCppCommandDeclaration((void *)StopElevator, "StopElevator", {});
        lemonscript::AvailableCppCommandDeclaration *stopDriving = new lemonscript::AvailableCppCommandDeclaration((void *)StopDriving, "StopDriving", {});
        lemonscript::AvailableCppCommandDeclaration *raiseWings = new lemonscript::AvailableCppCommandDeclaration((void *)RaiseWings, "RaiseWings", {});
        lemonscript::AvailableCppCommandDeclaration *pointTurn = new lemonscript::AvailableCppCommandDeclaration((void *)RaiseWings, "PointTurn", {FLOAT, FLOAT, BOOLEAN});
        lemonscript::AvailableCppCommandDeclaration *wait = new lemonscript::AvailableCppCommandDeclaration((void *)Wait, "Wait", {INT});
        lemonscript::AvailableCppCommandDeclaration *testBool = new lemonscript::AvailableCppCommandDeclaration((void *)TestBool, "TestBool", {BOOLEAN, BOOLEAN});

        
        std::vector<const lemonscript::AvailableCppCommandDeclaration *> commands = {driveStraight3, driveStraight2, driveStraight4, deployChokehold, calibrateElevator, stopElevator, stopDriving, raiseWings, pointTurn, wait, testBool};
        
        lemonscript::LemonScriptState *state = new lemonscript::LemonScriptState();
        state->declareAvailableCppCommands(commands);
        
        std::string fileName = "test_import.auto";
        lemonscript::LemonScriptCompiler *compiler = new lemonscript::LemonScriptCompiler(fileName, state);
        
        while (true) {
            bool isDone = compiler->PeriodicUpdate();
            if(isDone) { break; }
        }
        
        delete compiler;
        delete state;
        
        state = new lemonscript::LemonScriptState();
        state->declareAvailableCppCommands(commands);
        
        compiler = new lemonscript::LemonScriptCompiler(fileName, state);
        
        while (true) {
            bool isDone = compiler->PeriodicUpdate();
            if(isDone) { break; }
        }
        
        delete compiler;
        delete state;
        
    } catch (std::string error) {
        std::cerr << error << std::endl;
    }

    return 0;
}