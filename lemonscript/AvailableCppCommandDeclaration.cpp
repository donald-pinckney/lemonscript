//
//  AvailableCppCommand.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include "AvailableCppCommandDeclaration.h"

using lemonscript::DataType;

std::string dataTypeDescription(DataType t) {
    if(t == DataType::INT) return "INT";
    if(t == DataType::FLOAT) return "FLOAT";
    if(t == DataType::BOOLEAN) return "BOOLEAN";
    return "ERROR_TYPE";
}