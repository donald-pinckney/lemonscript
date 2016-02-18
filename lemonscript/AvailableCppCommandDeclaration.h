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

typedef enum {
    INT,
    FLOAT,
    BOOLEAN
} DataType;

std::string dataTypeDescription(DataType t);


class lemonscript::AvailableCppCommandDeclaration {

public:
    
    std::string functionName; // This function name has been camel-cased, and is in final form for C++
    void *func;
    std::vector<DataType> parameters; // in order from left to right
    
    
    AvailableCppCommandDeclaration(void *f, const std::string &name, const std::vector<DataType> &ps) : functionName(name), func(f), parameters(ps) { };
    
};


#endif /* AvailableCppCommand_hpp */
