//
//  LemonScriptState.hpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef LemonScriptState_hpp
#define LemonScriptState_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#include "AvailableCppCommandDeclaration.h"

class LemonScriptState {
    
    // Will contain things such as variable bindings, etc.
    std::map<std::string, void *> variableAddresses;
    std::map<std::string, DataType> variableTypes;

    std::map<std::string, std::vector<const AvailableCppCommandDeclaration *> > availableCppCommands;
    
    
public:
    
    void *userData = NULL;
    
    // Declaration functions
    void declareVariable(int line, const std::string &name, DataType type, void *pointerToValue);
    void declareAvailableCppCommand(const AvailableCppCommandDeclaration *decl);
    
    // Lookup functions
    void *addressOfVariable(const std::string &variableName) const;
    
    // Undefined what is returned if variableName does not exist
    DataType typeOfVariable(const std::string &variableName) const;
    
    const AvailableCppCommandDeclaration *lookupCommandDeclaration(const std::string &name, const std::vector<DataType> &parameterTypes) const;
    
};

#endif /* LemonScriptState_hpp */
