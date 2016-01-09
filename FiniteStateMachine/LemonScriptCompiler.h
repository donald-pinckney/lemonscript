//
//  LemonScriptCompiler.hpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/30/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef LemonScriptCompiler_hpp
#define LemonScriptCompiler_hpp

#include <stdio.h>
#include <sstream>
#include <vector>

#include "LemonScriptTokenizer.h"
#include "IteratedFiniteStateMachine.h"
#include "AvailableCppCommandDeclaration.h"
#include "LemonScriptState.h"

class LemonScriptCompiler {
    
    std::istream *input;
    LemonScriptState state;
    LemonScriptTokenizer tokenizer;
    
public:
    
    LemonScriptCompiler(const std::string &toParse, const std::vector<const AvailableCppCommandDeclaration *> commands) : tokenizer(toParse) {
        input = new std::istringstream(toParse);
        
        for (auto it = commands.begin(); it != commands.end(); ++it) {
            state.declareAvailableCppCommand(*it);
        }
    }
    LemonScriptCompiler(std::istream *toParse, const std::vector<const AvailableCppCommandDeclaration *> commands) : tokenizer(toParse) {
        input = toParse;
        
        for (auto it = commands.begin(); it != commands.end(); ++it) {
            state.declareAvailableCppCommand(*it);
        }
    }
    
    
    IteratedFiniteStateMachine *compile();
};

#endif /* LemonScriptCompiler_hpp */
