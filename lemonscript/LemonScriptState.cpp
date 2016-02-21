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

lemonscript::LemonScriptState::~LemonScriptState() {
    LemonScriptSymbolTable::freeVariables();
}

void lemonscript::LemonScriptState::declareGlobalVariable(int line, const std::string &name, DataType type, void *pointerToValue) {
    symbolStack.declareGlobalVariable(line, name, type, pointerToValue);
}

void lemonscript::LemonScriptState::declareVariable(int line, const std::string &name, DataType type, void *pointerToValue) {
    symbolStack.declareVariable(line, name, type, pointerToValue);
}

void lemonscript::LemonScriptState::pushScope() {
    symbolStack.pushScope();
}

void lemonscript::LemonScriptState::popScope() {
    symbolStack.popScope();
}

LemonScriptSymbolTableStack lemonscript::LemonScriptState::getScope() {
    return symbolStack;
}

void lemonscript::LemonScriptState::restoreScope(const LemonScriptSymbolTableStack &scope) {
    symbolStack = scope;
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
    return symbolStack.addressOfVariable(variableName);
}

DataType lemonscript::LemonScriptState::typeOfVariable(const std::string &variableName) const {
    return symbolStack.typeOfVariable(variableName);
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