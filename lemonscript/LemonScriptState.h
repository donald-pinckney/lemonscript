//
//  LemonScriptState.hpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef LemonScriptState_hpp
#define LemonScriptState_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#include "AvailableCppCommandDeclaration.h"
#include "LemonScriptSymbolTableStack.h"

#include "lemonscript.h"

class lemonscript::LemonScriptState {
    
    LemonScriptSymbolTableStack symbolStack;
    std::map<std::string, std::vector<const AvailableCppCommandDeclaration *> > availableCppCommands;
    
public:
    ~LemonScriptState();
    
    void *userData = NULL;
    
    // Declaration functions
    void declareGlobalVariable(int line, const std::string &name, DataType type, void *pointerToValue);
    void declareVariable(int line, const std::string &name, DataType type, void *pointerToValue);
    
    // Symbol stack methods
    void pushScope();
    void popScope();
    
    // Please use these 2 methods sparingly...
    LemonScriptSymbolTableStack getScope(); // Warning, don't modify the returned stack.
    void restoreScope(const LemonScriptSymbolTableStack &scope);
    
    
    
    void declareAvailableCppCommand(const AvailableCppCommandDeclaration *decl);
    void declareAvailableCppCommands(const std::vector<const AvailableCppCommandDeclaration *> decls);
    
    // Lookup functions
    void *addressOfVariable(const std::string &variableName) const;
    
    // Undefined what is returned if variableName does not exist
    DataType typeOfVariable(const std::string &variableName) const;
    
    const AvailableCppCommandDeclaration *lookupCommandDeclaration(const std::string &name, const std::vector<DataType> &parameterTypes) const;
};

#endif /* LemonScriptState_hpp */
