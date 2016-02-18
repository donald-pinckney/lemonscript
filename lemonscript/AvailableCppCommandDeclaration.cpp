//
//  AvailableCppCommand.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include "AvailableCppCommandDeclaration.h"

std::string dataTypeDescription(DataType t) {
    if(t == INT) return "INT";
    if(t == FLOAT) return "FLOAT";
    if(t == BOOLEAN) return "BOOLEAN";
    return "ERROR_TYPE";
}