//
//  LemonScriptSymbolTable.hpp
//  lemonscript
//
//  Created by Donald Pinckney on 2/6/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#ifndef LemonScriptSymbolTable_hpp
#define LemonScriptSymbolTable_hpp

#include <stdio.h>
#include <string>
#include <map>
#include "AvailableCppCommandDeclaration.h"

class LemonScriptSymbolTable {
    
    // Will contain things such as variable bindings, etc.
    std::map<std::string, void *> variableAddresses;
    std::map<std::string, DataType> variableTypes;
    
public:
    // Declaration function
    void declareVariable(int line, const std::string &name, DataType type, void *pointerToValue);

    
    // Lookup functions
    // Returns NULL if variableName is not in the symbol table
    void *addressOfVariable(const std::string &variableName) const;
    
    // Undefined what is returned if variableName does not exist
    DataType typeOfVariable(const std::string &variableName) const;
};

#endif /* LemonScriptSymbolTable_hpp */
