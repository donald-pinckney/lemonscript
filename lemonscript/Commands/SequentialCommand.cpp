//
//  SequentialCommand.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 1/16/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include "SequentialCommand.h"
#include "LemonScriptTokenizer.h"

#include "CppCommand.h"
#include "WhileAlsoCommand.h"
#include "CompleteAnyCommand.h"
#include "CompleteAllCommand.h"

lemonscript::SequentialCommand::SequentialCommand(int l, const LemonScriptState &state, const std::string &sequenceString) : Command(l, state) {
    LemonScriptTokenizer tokenizer(sequenceString);
    
    
    std::string token;
    TokenType type;
    int lineNum;
    
    while(true) {
        std::tie(token, type, lineNum) = tokenizer.nextToken();
        if(type == NOT_A_TOKEN) {
            break;
        }
        
        Command *command;
        if(type == CppToken) {
            command = new CppCommand(l, state, token);
        } else if(type == WhileAlsoToken) {
            command = new WhileAlsoCommand(l, state, token);
        } else if(type == CompleteAnyToken) {
            command = new CompleteAnyCommand(l, state, token);
        } else if(type == CompleteAllToken) {
            command = new CompleteAllCommand(l, state, token);
        }
        
        sequence.push_back(command);
    }
}

bool lemonscript::SequentialCommand::Update() {
    Command *currentCommand = sequence[currentIndex];
    bool isDone = currentCommand->Update();
    
    // If the last command just finished, then we are done
    if(isDone && currentIndex == sequence.size() - 1) {
        return true;
    } else if(isDone) {
        // If a command other than the last finished, go to next command
        currentIndex++;
    }
    
    return false;
}