//
//  LemonScriptState.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "LemonScriptState.h"


void lemonscript::LemonScriptState::declareVariable(int line, const std::string &name, DataType type, void *pointerToValue) {
    
    if(variableAddresses.find(name) != variableAddresses.end()) {
        throw "Line " + std::to_string(line) + ":\nDuplicate variable definition: " + name;
    }
    
    void *address;
    switch (type) {
        case INT:
            address = malloc(sizeof(int));
            memcpy(address, pointerToValue, sizeof(int));
            break;
            
        case FLOAT:
            address = malloc(sizeof(float));
            memcpy(address, pointerToValue, sizeof(float));
            break;
            
        case BOOLEAN:
            address = malloc(sizeof(bool));
            memcpy(address, pointerToValue, sizeof(bool));
            break;
            
        default:
            break;
    }
    
    variableAddresses[name] = address;
    variableTypes[name] = type;
}

void lemonscript::LemonScriptState::declareAvailableCppCommand(const AvailableCppCommandDeclaration *decl) {
    std::string name = decl->functionName;
    std::vector<const AvailableCppCommandDeclaration *> &commands = availableCppCommands[name];
    for (auto it = commands.begin(); it != commands.end(); ++it) {
        if((*it)->parameters == decl->parameters) {
            throw "Duplicate command definition with params: " + name;
        }
    }
    
    commands.push_back(decl);
}

void * lemonscript::LemonScriptState::addressOfVariable(const std::string &variableName) const {
    auto it = variableAddresses.find(variableName);
    if(it != variableAddresses.end()) {
        return it->second;
    } else {
        return NULL;
    }
}

DataType lemonscript::LemonScriptState::typeOfVariable(const std::string &variableName) const {
    auto it = variableTypes.find(variableName);
    
    if(it != variableTypes.end()) {
        return it->second;
    } else {
        return INT;
    }
}

const lemonscript::AvailableCppCommandDeclaration * lemonscript::LemonScriptState::lookupCommandDeclaration(const std::string &name, const std::vector<DataType> &parameterTypes) const {
    auto mapIt = availableCppCommands.find(name);
    if(mapIt == availableCppCommands.end()) {
        return NULL;
    }
    
    
    const std::vector<const AvailableCppCommandDeclaration *> &commands = mapIt->second;
    for (auto it = commands.begin(); it != commands.end(); ++it) {
        const AvailableCppCommandDeclaration *decl = *it;
        if(decl->parameters == parameterTypes) {
            return decl;
        }
    }
    
    return NULL;
}