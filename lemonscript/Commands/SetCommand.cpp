//
//  SetCommand.cpp
//  lemonscript
//
//  Created by Donald Pinckney on 2/6/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include <iostream>
#include <string.h>

#include "SetCommand.h"
#include "ParsingUtils.h"

lemonscript::SetCommand::SetCommand(int l, LemonScriptState *s, const std::string &commandString) : Command(l, *s) {
    state = s;
    
    size_t equalsPos = commandString.find("=");
    if(equalsPos == std::string::npos) {
        throw "Invalid syntax: No '=' found in SET command";
    }
    
    size_t SETPos = commandString.find("SET");
    if(SETPos == std::string::npos) {
        throw "Invalid syntax: No 'SET' found in SET command";
    }
    size_t startLhsPos = SETPos + 3;
    
    std::string lhs = ParsingUtils::trimWhitespace(commandString.substr(startLhsPos,  equalsPos - startLhsPos));
    std::string rhs = ParsingUtils::trimWhitespace(commandString.substr(equalsPos + 1));
    
    std::cout << lhs << std::endl;
    std::cout << rhs << std::endl;
    
    rhsExpression = new Expression(rhs, s);
    type = rhsExpression->getType();
    
    int zero;
    bzero(&zero, sizeof(int));
    
    state->declareVariable(l, lhs, rhsExpression->getType(), &zero);
    variableAddress = state->addressOfVariable(lhs);
}

bool lemonscript::SetCommand::Update() {
    rhsExpression->getValue(variableAddress);
    return true;
}