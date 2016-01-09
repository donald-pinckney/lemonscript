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
#include "auto_functions.h"
#include "LemonScriptTokenizer.h"

int main() {
    
    LemonScriptState state;
    
    
    try {
        int val = 1125;
        state.declareVariable(1, "SECOND_RC_ENCODER", INT, &val);
                
        
        AvailableCppCommandDeclaration *driveStraight3 = new AvailableCppCommandDeclaration((void *)DriveStraight_3, "DriveStraight", {FLOAT, INT, BOOLEAN});
        AvailableCppCommandDeclaration *driveStraight2 = new AvailableCppCommandDeclaration((void *)DriveStraight_2, "DriveStraight", {FLOAT, INT});

        AvailableCppCommandDeclaration *deployChokehold = new AvailableCppCommandDeclaration((void *)DeployChokehold, "DeployChokehold", {});
        
        state.declareAvailableCppCommand(driveStraight2);
        state.declareAvailableCppCommand(driveStraight3);
        state.declareAvailableCppCommand(deployChokehold);

        
        CppCommand test2Command(6, state, "drive straight: speed = -0.65, distance = SECOND_RC_ENCODER");
        
        while(true) {
            bool b = test2Command.Update();
            std::cout << b << std::endl;
            
            if(b) {
                break;
            }
        }
        
        
        
        CppCommand testCommand(5, state, "  deploy chokehold  ");
        testCommand.Update();
        
        
        
        
        
        
        
        
        std::ifstream ifs("CVR3Tote.auto");
        
        LemonScriptTokenizer tok(&ifs);
        
        while(true) {
            std::string token;
            TokenType type;
            int lineNum;
            
            std::tie(token, type, lineNum) = tok.nextToken();
            
            std::cout << "line " << lineNum << ", " << type << std::endl;
            std::cout << token << std::endl;
        }
        
        
    } catch (std::string error) {
        std::cerr << error << std::endl;
    }

//     drive straight: speed = -0.65, distance = SECOND_RC_ENCODER
    return 0;
}