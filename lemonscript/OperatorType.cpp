//
//  OperatorType.cpp
//  lemonscript
//
//  Created by Donald Pinckney on 2/28/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include "OperatorType.h"

std::ostream & operator<<(std::ostream &o, lemonscript_expressions::OperatorType opType) {
    o << opType.operatorText;
    return o;
}