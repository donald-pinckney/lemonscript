//
//  CompleteAllCommand.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 1/16/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include "CompleteAllCommand.h"

#include "ParsingUtils.h"

lemonscript::CompleteAllCommand::CompleteAllCommand(int l, const LemonScriptState &s, const std::string &commandString) : Command(l, s) {
    const std::string allDelim = "COMPLETE ALL:\n";
    size_t allLoc = commandString.find(allDelim);
    size_t endOfAllLoc = allLoc + allDelim.length();
    
    // Get the while and also bodies
    std::string allBody = commandString.substr(endOfAllLoc);
    
    // Un-indent them before parsing
    allBody = ParsingUtils::decreaseIndent(allBody);
    
    // Parse the bodies
#warning TODO: Fix line number parameter.
    allCommands = new SimultaneousCommand(l, s, allBody);
}

bool lemonscript::CompleteAllCommand::Update() {
    return allCommands->Update();
}