//
//  Expression.cpp
//  lemonscript
//
//  Created by Donald Pinckney on 2/6/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include "Expression.h"

#include <string.h>

using namespace lemonscript_expressions;
using lemonscript::DataType;
using namespace std;


Expression::Expression(const std::string &str, const lemonscript::LemonScriptState *state, int lineNum) {
    
    
}

Expression::~Expression() {
    
}

bool Expression::isConstant() {
    return isConst;
}

DataType Expression::getType() {
    return t;
}

void Expression::getValue(void *p) {
    size_t dataSize;
    if (t == lemonscript::DataType::INT) {
        dataSize = sizeof(int);
    } else if(t == lemonscript::DataType::FLOAT) {
        dataSize = sizeof(float);
    } else {
        dataSize = sizeof(bool);
    }
    
    if(isConst) {
        memcpy(p, constValue, dataSize);
        return;
    }
    
//    ExpressionDesc desc = tree->evaluate();
//    t = desc.type;
//    
//    memcpy(p, desc.value, dataSize);
//    
//    ExpressionTree::freeHeap();
}