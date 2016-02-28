//
//  ExpressionParser.hpp
//  lemonscript
//
//  Created by Donald Pinckney on 2/22/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#ifndef ExpressionParser_hpp
#define ExpressionParser_hpp

#include <stdio.h>
#include <string>
#include <set>

#include "expressions.h"

#include "ExpressionScanner.h"

enum class lemonscript_expressions::NonTerminal {
    expression,
    parenthesized_expression,
    prefix_expression,
    binary_expression,
    binary_expressions,
    postfix_expression,
    primary_expression,
    prefix_operator,
    binary_operator,
    postfix_operator,
    _operator,
    operator_character,
    identifier,
    identifier_character,
    literal,
    boolean_literal,
    numeric_literal,
    integer_literal,
    floating_point_literal,
    decimal_fraction,
    decimal_literal,
    alpha,
    digit
};

class lemonscript_expressions::ExpressionParser {
    ExpressionScanner scanner;
    Token tok;
    void scan();
    void parse_error(const std::string &s);
    std::string mustbe(TK tk);
    bool is(TK tk);
    bool inFirstSet(NonTerminal nt);
    std::set<TK> firstSet(NonTerminal nt);
    
    void expression();
    void parenthesized_expression();
    
    void prefix_expression();
    
    void binary_expression();
    void binary_expressions();
    
    void postfix_expression();
    void function_call_expression();
    
    void primary_expression();
    
    void prefix_operator();
    void binary_operator();
    void postfix_operator();
    
    void _operator();
    void operator_character();
    
    void identifier();
    void identifier_character();
    
    void literal();
    void boolean_literal();
    void numeric_literal();
    
    void integer_literal();
    void floating_point_literal();
    void decimal_fraction();
    void decimal_literal();
    
    void alpha();
    void digit();
    
public:
    ExpressionParser(const std::string &toParse);
};

#endif /* ExpressionParser_hpp */
