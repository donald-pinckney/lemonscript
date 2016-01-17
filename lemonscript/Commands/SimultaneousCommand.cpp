//
//  SimultaneousCommand.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 1/16/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include "SimultaneousCommand.h"
#include "LemonScriptTokenizer.h"

#include "CppCommand.h"
#include "WhileAlsoCommand.h"
#include "CompleteAnyCommand.h"
#include "CompleteAllCommand.h"

lemonscript::SimultaneousCommand::SimultaneousCommand(int l, const LemonScriptState &state, const std::string &sequenceString) : Command(l, state) {
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
        
        commands.push_back(command);
    }
    
    doneCommands = std::vector<bool>(commands.size(), false);
}


bool lemonscript::SimultaneousCommand::Update() {
    return Update(false);
}

bool lemonscript::SimultaneousCommand::Update(bool hard) {
    
    size_t len = commands.size();
    bool allDone = true;
    bool anyDone = false;
    for (size_t i = 0; i < len; i++) {
        bool alreadyDone = doneCommands[i];
        if(alreadyDone && !hard) {
            anyDone = true;
            continue;
        }
        
        bool done = commands[i]->Update();
        doneCommands[i] = done;
        if(done) {
            anyDone = true;
        }
        if(!done) {
            allDone = false;
        }
    }
    
    if(allDone) {
        state = SimultaneousCommmandState::AllComplete;
    } else if(anyDone) {
        state = SimultaneousCommmandState::AnyComplete;
    }
    
    return allDone;
}
