//
//  expressions.h
//  lemonscript
//
//  Created by Donald Pinckney on 2/22/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#ifndef expressions_h
#define expressions_h

#include <iostream>

namespace lemonscript_expressions {
    class Expression;
    class ExpressionScanner;
    class ExpressionParser;
    struct Token;
    enum class TK : char;
    enum class NonTerminal;
    std::ostream & operator<<(std::ostream &os, const Token &tok);
}

#endif /* expressions_h */
