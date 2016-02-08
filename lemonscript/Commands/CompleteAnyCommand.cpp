//
//  CompleteAnyToken.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 1/16/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include "CompleteAnyCommand.h"
#include "ParsingUtils.h"

lemonscript::CompleteAnyCommand::CompleteAnyCommand(int l, LemonScriptState &s, const std::string &commandString) : Command(l, s) {
    const std::string anyDelim = "COMPLETE ANY:\n";
    size_t anyLoc = commandString.find(anyDelim);
    size_t endOfAnyLoc = anyLoc + anyDelim.length();
    
    // Get the while and also bodies
    std::string anyBody = commandString.substr(endOfAnyLoc);
    
    // Un-indent them before parsing
    anyBody = ParsingUtils::decreaseIndent(anyBody);
    
    // Parse the bodies
#warning TODO: Fix line number parameter.
    anyCommands = new SimultaneousCommand(l, s, anyBody);
}


bool lemonscript::CompleteAnyCommand::Update() {
    
    anyCommands->Update();
    
    return anyCommands->getState() == SimultaneousCommmandState::AnyComplete || anyCommands->getState() == SimultaneousCommmandState::AllComplete;
}