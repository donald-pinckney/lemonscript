//
//  AvailableCppCommand.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include "AvailableCppCommandDeclaration.h"

#include <string.h>
#include <strings.h>

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

int lemonscript::DataTypeIntCastFromTo(DataType from, DataType to, int value) {
    int retVal;
    bzero(&retVal, sizeof(int));
    
    if(from == to) {
        return value;
    } else if(from == DataType::BOOLEAN) {
        bool boolVal = *(bool *)(&value);
        
        if(to == DataType::INT) {
            int castValue = (int)boolVal;
            memcpy(&retVal, &castValue, sizeof(int));
        } else if(to == DataType::FLOAT) {
            float castValue = (float)boolVal;
            memcpy(&retVal, &castValue, sizeof(float));
        }
        
    } else if(from == DataType::INT) {
        int intVal = *(int *)(&value);
        
        if(to == DataType::BOOLEAN) {
            bool castValue = (bool)intVal;
            memcpy(&retVal, &castValue, sizeof(bool));
        } else if(to == DataType::FLOAT) {
            float castValue = (float)intVal;
            memcpy(&retVal, &castValue, sizeof(float));
        }
        
    } else if(from == DataType::FLOAT) {
        float floatVal = *(float *)(&value);
        
        if(to == DataType::INT) {
            int castValue = (int)floatVal;
            memcpy(&retVal, &castValue, sizeof(int));
        } else if(to == DataType::BOOLEAN) {
            bool castValue = (bool)floatVal;
            memcpy(&retVal, &castValue, sizeof(bool));
        }
    }
    
    return retVal;
}




std::string dataTypeDescription(DataType t) {
    if(t == DataType::INT) return "INT";
    if(t == DataType::FLOAT) return "FLOAT";
    if(t == DataType::BOOLEAN) return "BOOLEAN";
    if(t == DataType::TYPE) return "TYPE";
    return "ERROR_TYPE";
}