//
//  ExpressionParser.cpp
//  lemonscript
//
//  Created by Donald Pinckney on 2/22/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include "ExpressionParser.h"

using namespace lemonscript_expressions;
using namespace std;

ExpressionParser::ExpressionParser(const string &toParse) : scanner(toParse), tok(scanner.scan()) {
    expression();
    
    if(tok.kind != TK::END_OF_FILE) {
        parse_error("Junk after end of expression");
    }
}


//  expression = prefix_expression [binary_expressions];
void ExpressionParser::expression() {
    prefix_expression();
    
    if(inFirstSet(NonTerminal::binary_expressions)) {
        binary_expressions();
    }
}

//  parenthesized_expression = "(" expression {"," expression} ")";
void ExpressionParser::parenthesized_expression() {
    mustbe(TK::LPAREN);
    
    expression();
    
    while (is(TK::COMMA)) {
        mustbe(TK::COMMA);
        expression();
    }
    
    mustbe(TK::RPAREN);
}

//  prefix_expression = [prefix_operator] postfix_expression;
void ExpressionParser::prefix_expression() {
    if(inFirstSet(NonTerminal::prefix_operator)) {
        prefix_operator();
    }
    postfix_expression();
}

//  binary_expression = binary_operator prefix_expression;
void ExpressionParser::binary_expression() {
    binary_operator();
    prefix_expression();
}

//  binary_expressions = binary_expression [binary_expressions];
void ExpressionParser::binary_expressions() {
    binary_expression();
    
    if(inFirstSet(NonTerminal::binary_expressions)) {
        binary_expressions();
    }
}


//  postfix_expression = primary_expression
void ExpressionParser::postfix_expression() {
    primary_expression();
}

//  primary_expression = identifier | literal | parenthesized_expression;
void ExpressionParser::primary_expression() {
    if(inFirstSet(NonTerminal::identifier)) {
        identifier();
    } else if(inFirstSet(NonTerminal::literal)) {
        literal();
    } else if(inFirstSet(NonTerminal::parenthesized_expression)) {
        parenthesized_expression();
    } else {
        parse_error("Missing token");
    }
}

//  prefix_operator = operator;
void ExpressionParser::prefix_operator() {
    _operator();
}

//  binary_operator = operator;
void ExpressionParser::binary_operator() {
    _operator();
}

//  postfix_operator = operator;
void ExpressionParser::postfix_operator() {
    _operator();
}

//  operator = operator_character {operator_character};
void ExpressionParser::_operator() {
    operator_character();
    while (inFirstSet(NonTerminal::operator_character)) {
        operator_character();
    }
}

//  operator_character = "/" | "*" | "=" | "-" | "+" | "!" | "%" | "<" | ">" | "&" | "|" | "^";
void ExpressionParser::operator_character() {
    if (is(TK::FORWARD_SLASH)) {
        mustbe(TK::FORWARD_SLASH);
    } else if (is(TK::ASTERISK)) {
        mustbe(TK::ASTERISK);
    } else if (is(TK::EQUALS)) {
        mustbe(TK::EQUALS);
    } else if (is(TK::MINUS)) {
        mustbe(TK::MINUS);
    } else if (is(TK::PLUS)) {
        mustbe(TK::PLUS);
    } else if (is(TK::EXCLAMATION_MARK)) {
        mustbe(TK::EXCLAMATION_MARK);
    } else if (is(TK::PERCENT)) {
        mustbe(TK::PERCENT);
    } else if (is(TK::LANGLE)) {
        mustbe(TK::LANGLE);
    } else if (is(TK::RANGLE)) {
        mustbe(TK::RANGLE);
    } else if (is(TK::AMPERSAND)) {
        mustbe(TK::AMPERSAND);
    } else if (is(TK::PIPE)) {
        mustbe(TK::PIPE);
    } else if (is(TK::CARET)) {
        mustbe(TK::CARET);
    } else {
        parse_error("Missing token");
    }
}

//  identifier = alpha {identifier_character};
void ExpressionParser::identifier() {
    alpha();
    
    while (inFirstSet(NonTerminal::identifier_character)) {
        identifier_character();
    }
}

//  identifier_character = alpha | digit;
void ExpressionParser::identifier_character() {
    if(inFirstSet(NonTerminal::alpha)) {
        alpha();
    } else if(inFirstSet(NonTerminal::digit)) {
        digit();
    } else {
        parse_error("Missing token");
    }
}

//  literal = numeric_literal | boolean_literal;
void ExpressionParser::literal() {
    if(inFirstSet(NonTerminal::numeric_literal)) {
        numeric_literal();
    } else if(inFirstSet(NonTerminal::boolean_literal)) {
        boolean_literal();
    } else {
        parse_error("Missing token");
    }
}

//  boolean_literal = "true" | "false";
void ExpressionParser::boolean_literal() {
    if(is(TK::BOOLEAN_TRUE)) {
        mustbe(TK::BOOLEAN_TRUE);
    } else if(is(TK::BOOLEAN_FALSE)) {
        mustbe(TK::BOOLEAN_FALSE);
    } else {
        parse_error("Missing token");
    }
}

//  numeric_literal = ["-"] integer_literal | ["-"] floating_point_literal;
void ExpressionParser::numeric_literal() {
    if(is(TK::MINUS)) {
        mustbe(TK::MINUS);
    }
    
    if(inFirstSet(NonTerminal::integer_literal)) {
        integer_literal();
    } else if(inFirstSet(NonTerminal::floating_point_literal)) {
        floating_point_literal();
    } else {
        parse_error("Missing token");
    }
}

//  integer_literal = decimal_literal;
void ExpressionParser::integer_literal() {
    decimal_literal();
}

//  floating_point_literal = decimal_literal [decimal_fraction];
void ExpressionParser::floating_point_literal() {
    decimal_literal();
    
    if(inFirstSet(NonTerminal::decimal_fraction)) {
        decimal_fraction();
    }
}

//  decimal_fraction = "." decimal_literal;
void ExpressionParser::decimal_fraction() {
    mustbe(TK::PERIOD);
    decimal_literal();
}

//  decimal_literal = digit {digit};
void ExpressionParser::decimal_literal() {
    digit();
    while (inFirstSet(NonTerminal::digit)) {
        digit();
    }
}

//  alpha = "a".."z" | "A".."Z";
void ExpressionParser::alpha() {
    mustbe(TK::ALPHA);
}

//  digit = "0".."9";
void ExpressionParser::digit() {
    mustbe(TK::DIGIT);
}


bool ExpressionParser::is(lemonscript_expressions::TK tk) {
    return tok.kind == tk;
}

bool ExpressionParser::inFirstSet(lemonscript_expressions::NonTerminal nt) {
    set<TK> fs = firstSet(nt);
    return fs.find(tok.kind) != fs.end();
}

template <typename T>
set<T> sunion(set<T> x, const set<T> &y) {
    for (auto it = y.begin(); it != y.end(); ++it) {
        x.insert(*it);
    }
    return x;
}

set<TK> ExpressionParser::firstSet(lemonscript_expressions::NonTerminal nt) {
    switch (nt) {
        case NonTerminal::expression:
            return firstSet(NonTerminal::prefix_expression);
        case NonTerminal::parenthesized_expression:
            return {TK::LPAREN};
        case NonTerminal::prefix_expression:
            return firstSet(NonTerminal::prefix_operator);
        case NonTerminal::binary_expression:
            return firstSet(NonTerminal::binary_operator);
        case NonTerminal::binary_expressions:
            return firstSet(NonTerminal::binary_expression);
        case NonTerminal::postfix_expression:
            return firstSet(NonTerminal::primary_expression);
        case NonTerminal::primary_expression:
            return sunion(sunion(firstSet(NonTerminal::identifier), firstSet(NonTerminal::literal)), firstSet(NonTerminal::parenthesized_expression));
        case NonTerminal::prefix_operator:
            return firstSet(NonTerminal::_operator);
        case NonTerminal::binary_operator:
            return firstSet(NonTerminal::_operator);
        case NonTerminal::postfix_operator:
            return firstSet(NonTerminal::_operator);
        case NonTerminal::_operator:
            return firstSet(NonTerminal::operator_character);
            
        case NonTerminal::operator_character:
            return {TK::FORWARD_SLASH, TK::ASTERISK, TK::EQUALS, TK::MINUS, TK::PLUS, TK::EXCLAMATION_MARK, TK::PERCENT, TK::LANGLE, TK::RANGLE, TK::AMPERSAND, TK::PIPE, TK::CARET};
            
        case NonTerminal::identifier:
            return firstSet(NonTerminal::alpha);
        case NonTerminal::identifier_character:
            return sunion(firstSet(NonTerminal::alpha), firstSet(NonTerminal::digit));
        case NonTerminal::literal:
            return sunion(firstSet(NonTerminal::numeric_literal), firstSet(NonTerminal::boolean_literal));
        case NonTerminal::boolean_literal:
            return {TK::BOOLEAN_TRUE, TK::BOOLEAN_FALSE};
        case NonTerminal::numeric_literal:
            return sunion(sunion({TK::MINUS}, firstSet(NonTerminal::integer_literal)), firstSet(NonTerminal::floating_point_literal));
        case NonTerminal::integer_literal:
            return firstSet(NonTerminal::decimal_literal);
        case NonTerminal::floating_point_literal:
            return firstSet(NonTerminal::decimal_literal);
        case NonTerminal::decimal_fraction:
            return {TK::PERIOD};
        case NonTerminal::decimal_literal:
            return firstSet(NonTerminal::digit);
        case NonTerminal::alpha:
            return {TK::ALPHA};
        case NonTerminal::digit:
            return {TK::DIGIT};
    }
}

void ExpressionParser::scan() {
    tok = scanner.scan();
}

string ExpressionParser::mustbe(TK tk) {
    if( tok.kind != tk ) {
        parse_error("mustbe: want " + to_string(static_cast<char>(tk)) + ", got " + tok.description());
    }
    string temp = tok.string;
    scan();
    
    return temp;
}

void ExpressionParser::parse_error(const string &s) {
    throw s;
}




