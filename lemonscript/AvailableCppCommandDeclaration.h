//
//  AvailableCppCommand.hpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef AvailableCppCommand_hpp
#define AvailableCppCommand_hpp

#include <stdio.h>
#include <vector>
#include <string>

#include "lemonscript.h"

namespace lemonscript {
    enum class DataType {
        INT, FLOAT, BOOLEAN, TYPE
    };
    
    bool DataTypeIsSubtypeOf(DataType subtype, DataType type);
    
    int DataTypeIntCastFromTo(DataType from, DataType to, int value);

    template <typename T>
    int DataTypeBuildInt(T val) {
        int retVal;
        bzero(&retVal, sizeof(int));
        
        memcpy(&retVal, &val, sizeof(T));
        
        return retVal;
    }

}


std::string dataTypeDescription(lemonscript::DataType t);


class lemonscript::AvailableCppCommandDeclaration {

public:
    
    std::string functionName; // This function name has been camel-cased, and is in final form for C++
    void *func;
    std::vector<DataType> parameters; // in order from left to right
    
    
    AvailableCppCommandDeclaration(void *f, const std::string &name, const std::vector<DataType> &ps) : functionName(name), func(f), parameters(ps) { };
    
};


#endif /* AvailableCppCommand_hpp */
