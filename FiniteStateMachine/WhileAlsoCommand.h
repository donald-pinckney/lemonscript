//
//  WhileAlsoCommand.hpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/30/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef WhileAlsoCommand_hpp
#define WhileAlsoCommand_hpp

#include <stdio.h>

#include "Command.h"

class WhileAlsoCommand : public Command {
    
    const Command *whileCondition = NULL;
    
    std::vector<const Command *>alsoCommands;
    
    
public:
    WhileAlsoCommand(int l, const LemonScriptState &s, const std::string &commandString);
    
    bool Update() const;
    
};


#endif /* WhileAlsoCommand_hpp */
