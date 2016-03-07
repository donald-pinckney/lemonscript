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

#include "ExpressionParser.h"

#include "ExpressionTree.h"

using namespace lemonscript;
using namespace lemonscript_expressions;

int main() {
    
    try {        
        
        lemonscript::AvailableCppCommandDeclaration *driveStraight3 = new lemonscript::AvailableCppCommandDeclaration((void *)DriveStraight_3, "DriveStraight", {DataType::FLOAT, DataType::INT, DataType::BOOLEAN});
        lemonscript::AvailableCppCommandDeclaration *driveStraight2 = new lemonscript::AvailableCppCommandDeclaration((void *)DriveStraight_2, "DriveStraight", {DataType::FLOAT, DataType::INT});
        lemonscript::AvailableCppCommandDeclaration *driveStraight4 = new lemonscript::AvailableCppCommandDeclaration((void *)DriveStraight_4, "DriveStraight", {DataType::FLOAT, DataType::FLOAT});
        lemonscript::AvailableCppCommandDeclaration *deployChokehold = new lemonscript::AvailableCppCommandDeclaration((void *)DeployChokehold, "DeployChokehold", {});
        lemonscript::AvailableCppCommandDeclaration *calibrateElevator = new lemonscript::AvailableCppCommandDeclaration((void *)CalibrateElevator, "CalibrateElevator", {});
        lemonscript::AvailableCppCommandDeclaration *stopElevator = new lemonscript::AvailableCppCommandDeclaration((void *)StopElevator, "StopElevator", {});
        lemonscript::AvailableCppCommandDeclaration *stopDriving = new lemonscript::AvailableCppCommandDeclaration((void *)StopDriving, "StopDriving", {});
        lemonscript::AvailableCppCommandDeclaration *raiseWings = new lemonscript::AvailableCppCommandDeclaration((void *)RaiseWings, "RaiseWings", {});
        lemonscript::AvailableCppCommandDeclaration *pointTurn = new lemonscript::AvailableCppCommandDeclaration((void *)PointTurn, "PointTurn", {DataType::FLOAT, DataType::FLOAT, DataType::BOOLEAN});
        lemonscript::AvailableCppCommandDeclaration *pointTurn2 = new lemonscript::AvailableCppCommandDeclaration((void *)PointTurn2, "PointTurn", {DataType::FLOAT});

        lemonscript::AvailableCppCommandDeclaration *wait = new lemonscript::AvailableCppCommandDeclaration((void *)Wait, "Wait", {DataType::INT});
        lemonscript::AvailableCppCommandDeclaration *wait5 = new lemonscript::AvailableCppCommandDeclaration((void *)Wait5, "Wait5", {});

        lemonscript::AvailableCppCommandDeclaration *testBool = new lemonscript::AvailableCppCommandDeclaration((void *)TestBool, "TestBool", {DataType::BOOLEAN, DataType::BOOLEAN});
        lemonscript::AvailableCppCommandDeclaration *printF = new lemonscript::AvailableCppCommandDeclaration((void *)PrintF, "Print", {DataType::FLOAT});
        lemonscript::AvailableCppCommandDeclaration *printI = new lemonscript::AvailableCppCommandDeclaration((void *)PrintI, "Print", {DataType::INT});
        lemonscript::AvailableCppCommandDeclaration *printB = new lemonscript::AvailableCppCommandDeclaration((void *)PrintB, "Print", {DataType::BOOLEAN});


        
        std::vector<const lemonscript::AvailableCppCommandDeclaration *> commands = {driveStraight3, driveStraight2, driveStraight4, deployChokehold, calibrateElevator, stopElevator, stopDriving, raiseWings, pointTurn, pointTurn2, wait, wait5, testBool, printF, printI, printB};
        
        lemonscript::LemonScriptState *state = new lemonscript::LemonScriptState();
        state->declareAvailableCppCommands(commands);
        
        

        std::string fileName = "test_run.auto";
        lemonscript::LemonScriptCompiler *compiler = new lemonscript::LemonScriptCompiler(fileName, state);
        
        while (true) {
            bool isDone = compiler->PeriodicUpdate();
            if(isDone) { break; }
        }
        
        delete compiler;
        delete state;
        
//        state = new lemonscript::LemonScriptState();
//        state->declareAvailableCppCommands(commands);
//        
//        compiler = new lemonscript::LemonScriptCompiler(fileName, state);
//        
//        while (true) {
//            bool isDone = compiler->PeriodicUpdate();
//            if(isDone) { break; }
//        }
//        
//        delete compiler;
//        delete state;
        
    } catch (std::string error) {
        std::cerr << error << std::endl;
    }

    return 0;
}