//
//  Expression.cpp
//  lemonscript
//
//  Created by Donald Pinckney on 2/6/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include "Expression.h"

lemonscript::Expression::Expression(const std::string &str, const lemonscript::LemonScriptState *state) {
    
}

bool lemonscript::Expression::isConstant() {
    return isConst;
}

DataType lemonscript::Expression::getType() {
    return t;
}

void lemonscript::Expression::getValue(void *p) {
    float i = 8;
    memcpy(p, &i, sizeof(float));
}