//
//  CompleteAllCommand.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 1/16/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include "CompleteAllCommand.h"

#include "ParsingUtils.h"

lemonscript::CompleteAllCommand::CompleteAllCommand(int l, LemonScriptState *s, const std::string &commandString) : Command(l, s) {
    const std::string allDelim = "COMPLETE ALL:\n";
    size_t allLoc = commandString.find(allDelim);
    size_t endOfAllLoc = allLoc + allDelim.length();
    
    // Get the while and also bodies
    std::string allBody = commandString.substr(endOfAllLoc);
    
    // Un-indent them before parsing
    allBody = ParsingUtils::decreaseIndent(allBody);
    
    // Parse the bodies
//#warning TODO: Fix line number parameter.
    
    s->pushScope();
    allCommands = new SimultaneousCommand(l, s, allBody);
    allScope = s->getScope();
    s->popScope();
}

lemonscript::CompleteAllCommand::~CompleteAllCommand() {
    delete allCommands;
}

bool lemonscript::CompleteAllCommand::Update() {
    
    LemonScriptSymbolTableStack currentScope = savedState->getScope();
    
    savedState->restoreScope(allScope);
    bool ret = allCommands->Update();
    
    savedState->restoreScope(currentScope);
    
    return ret;
}