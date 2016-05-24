//
//  mainLemonScript.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>


#include "PlayTestsShared.h"

#include <lemonscript/lemonscript.h>
#include <lemonscript/AvailableCppCommandDeclaration.h>
#include <lemonscript/LemonScriptCompiler.h>

using namespace lemonscript;
//using namespace lemonscript_expressions;

int main() {

    try {
        lemonscript::LemonScriptState *state = PlayTestsShared::play_tests_make_state();
        
        std::string fileName = "test_run.auto";
        lemonscript::LemonScriptCompiler *compiler = new lemonscript::LemonScriptCompiler(fileName, state);
        
        while (true) {
            bool isDone = compiler->PeriodicUpdate();
            if(isDone) { break; }
        }
        
        delete compiler;
        delete state;
    } catch (std::string error) {
        std::cerr << error << std::endl;
    }

    return 0;
}