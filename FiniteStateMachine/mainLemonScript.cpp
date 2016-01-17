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
        
    LemonScriptState state;
    
    
    try {
        int val = 1125;
        state.declareVariable(1, "SECOND_RC_ENCODER", INT, &val);
                
        
        AvailableCppCommandDeclaration *driveStraight3 = new AvailableCppCommandDeclaration((void *)DriveStraight_3, "DriveStraight", {FLOAT, INT, BOOLEAN});
        AvailableCppCommandDeclaration *driveStraight2 = new AvailableCppCommandDeclaration((void *)DriveStraight_2, "DriveStraight", {FLOAT, INT});
        AvailableCppCommandDeclaration *deployChokehold = new AvailableCppCommandDeclaration((void *)DeployChokehold, "DeployChokehold", {});
        AvailableCppCommandDeclaration *calibrateElevator = new AvailableCppCommandDeclaration((void *)CalibrateElevator, "CalibrateElevator", {});
        AvailableCppCommandDeclaration *stopElevator = new AvailableCppCommandDeclaration((void *)StopElevator, "StopElevator", {});
        AvailableCppCommandDeclaration *stopDriving = new AvailableCppCommandDeclaration((void *)StopDriving, "StopDriving", {});
        AvailableCppCommandDeclaration *raiseWings = new AvailableCppCommandDeclaration((void *)RaiseWings, "RaiseWings", {});

        std::vector<const AvailableCppCommandDeclaration *> commands = {driveStraight3, driveStraight2, deployChokehold, calibrateElevator, stopElevator, stopDriving, raiseWings};
        
        std::ifstream ifs("deploy chokehold.auto");
        LemonScriptCompiler compiler(ifs, commands, &state);
        
        while (true) {
            bool isDone = compiler.PeriodicUpdate();
            if(isDone) { break; }
        }
        
        
    } catch (std::string error) {
        std::cerr << error << std::endl;
    }

    return 0;
}