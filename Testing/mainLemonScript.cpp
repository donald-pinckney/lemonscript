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
        
    lemonscript::LemonScriptState state;
    
    
    try {
        int val = 1125;
        state.declareVariable(1, "SECOND_RC_ENCODER", INT, &val);
                
        
        lemonscript::AvailableCppCommandDeclaration *driveStraight3 = new lemonscript::AvailableCppCommandDeclaration((void *)DriveStraight_3, "DriveStraight", {FLOAT, INT, BOOLEAN});
        lemonscript::AvailableCppCommandDeclaration *driveStraight2 = new lemonscript::AvailableCppCommandDeclaration((void *)DriveStraight_2, "DriveStraight", {FLOAT, INT});
        lemonscript::AvailableCppCommandDeclaration *driveStraight4 = new lemonscript::AvailableCppCommandDeclaration((void *)DriveStraight_4, "DriveStraight", {FLOAT, FLOAT});
        lemonscript::AvailableCppCommandDeclaration *deployChokehold = new lemonscript::AvailableCppCommandDeclaration((void *)DeployChokehold, "DeployChokehold", {});
        lemonscript::AvailableCppCommandDeclaration *calibrateElevator = new lemonscript::AvailableCppCommandDeclaration((void *)CalibrateElevator, "CalibrateElevator", {});
        lemonscript::AvailableCppCommandDeclaration *stopElevator = new lemonscript::AvailableCppCommandDeclaration((void *)StopElevator, "StopElevator", {});
        lemonscript::AvailableCppCommandDeclaration *stopDriving = new lemonscript::AvailableCppCommandDeclaration((void *)StopDriving, "StopDriving", {});
        lemonscript::AvailableCppCommandDeclaration *raiseWings = new lemonscript::AvailableCppCommandDeclaration((void *)RaiseWings, "RaiseWings", {});

        std::vector<const lemonscript::AvailableCppCommandDeclaration *> commands = {driveStraight3, driveStraight2, driveStraight4, deployChokehold, calibrateElevator, stopElevator, stopDriving, raiseWings};
        
        std::ifstream ifs("twoBall2016.auto");
        lemonscript::LemonScriptCompiler compiler(ifs, commands, &state);
        
        while (true) {
            bool isDone = compiler.PeriodicUpdate();
            if(isDone) { break; }
        }
        
        
    } catch (std::string error) {
        std::cerr << error << std::endl;
    }

    return 0;
}