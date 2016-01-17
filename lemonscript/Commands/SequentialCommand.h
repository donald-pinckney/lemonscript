//
//  SequentialCommand.hpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 1/16/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#ifndef SequentialCommand_hpp
#define SequentialCommand_hpp

#include <stdio.h>
#include <vector>

#include "Command.h"

class SequentialCommand : public Command {

    std::vector<Command *> sequence;
    int currentIndex = 0;
public:
    SequentialCommand(int l, const LemonScriptState &s, const std::string &sequenceString);

    bool Update();
};

#endif /* SequentialCommand_hpp */
