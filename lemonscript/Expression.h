//
//  Expression.hpp
//  lemonscript
//
//  Created by Donald Pinckney on 2/6/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#ifndef Expression_hpp
#define Expression_hpp

#include <stdio.h>
#include <string>

#include "lemonscript.h"

#include "AvailableCppCommandDeclaration.h"
#include "LemonScriptState.h"
#include "ExpressionTree.h"

namespace lemonscript_expressions {

class Expression {
    
    
    bool isConst;
    DataType t;
    void *constValue;
    
    ExpressionTree *tree;
    
public:
    Expression(const std::string &str, const lemonscript::LemonScriptState *state, int lineNum);
    ~Expression();
    
    bool isConstant();
    DataType getType();
    void getValue(void *p);
};
    
}

#endif /* Expression_hpp */
