//
//  AvailableCppCommand.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include "AvailableCppCommandDeclaration.h"

using lemonscript::DataType;

// This could be build into a more general tree, but whatever
bool lemonscript::DataTypeIsSubtypeOf(DataType subtype, DataType type) {
    if(subtype == DataType::TYPE) {
        return subtype == type;
    } else if(subtype == DataType::BOOLEAN) {
        return subtype == type;
    } else if(subtype == DataType::FLOAT) {
        return subtype == type;
    } else if(subtype == DataType::INT) {
        if (type == DataType::FLOAT) {
            return true;
        }
        return subtype == type;
    }
    
    throw "Unknown type";
}

std::string dataTypeDescription(DataType t) {
    if(t == DataType::INT) return "INT";
    if(t == DataType::FLOAT) return "FLOAT";
    if(t == DataType::BOOLEAN) return "BOOLEAN";
    if(t == DataType::TYPE) return "TYPE";
    return "ERROR_TYPE";
}