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
#include "expressions.h"

#include "AvailableCppCommandDeclaration.h"
#include "LemonScriptState.h"

class lemonscript_expressions::Expression {
    
    bool isConst;
    lemonscript::DataType t;
    void *constValue;
    
//    ExpressionTree *tree;
    
public:
    Expression(const std::string &str, const lemonscript::LemonScriptState *state, int lineNum);
    ~Expression();
    
    bool isConstant();
    lemonscript::DataType getType();
    void getValue(void *p);
};


#endif /* Expression_hpp */
