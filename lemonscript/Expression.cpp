//
//  Expression.cpp
//  lemonscript
//
//  Created by Donald Pinckney on 2/6/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#include "Expression.h"

using namespace lemonscript_expressions;

int currentParseLine;
ExpressionDesc parseAtomType(string atomString, const lemonscript::LemonScriptState *state) {
    if(atomString == "false") {
        bool *bPtr = ExpressionTree::alloc<bool>();
        *bPtr = false;
        
        return ExpressionDesc(BOOLEAN, true, bPtr);
    } else if(atomString == "true") {
        bool *bPtr = ExpressionTree::alloc<bool>();
        *bPtr = true;
        
        return ExpressionDesc(BOOLEAN, true, bPtr);
    } else {
        // try to parse argument as an int
        try {
            int *iPtr = ExpressionTree::alloc<int>();
            
            if(atomString.find(".") != string::npos) {
                throw invalid_argument("ITS A FLOAT!");
            }
            *iPtr = stoi(atomString);
            
            return ExpressionDesc(INT, true, iPtr);
        } catch (invalid_argument &err) {
            
        }
        
        // try to parse argument as a float
        try {
            float *fPtr = ExpressionTree::alloc<float>();

            *fPtr = stof(atomString);
            
            return ExpressionDesc(FLOAT, true, fPtr);
        } catch (invalid_argument &err) {
            
        }
        
        
        void *address = state->addressOfVariable(atomString);
        if(address == NULL) {
            throw "Line " + to_string(currentParseLine) + ":\nUse of undeclared variable: " + atomString;
        }
        
        return ExpressionDesc(state->typeOfVariable(atomString), false, address);
    }
}

Expression::Expression(const std::string &str, const lemonscript::LemonScriptState *state, int lineNum) {
    
    currentParseLine = lineNum;
    
    function<ExpressionDesc(string)> exprDescSubstitutions = [state] (string atomString) {
        ExpressionDesc retVal = parseAtomType(atomString, state);
        
        return retVal;
    };
    
    tree = new ExpressionTree(str, exprDescSubstitutions);
    ExpressionDesc desc = tree->evaluate();
    
    t = desc.type;
    isConst = desc.isConst;
    
    constValue = NULL;
    if(isConst) {
        size_t dataSize;
        if (t == INT) {
            dataSize = sizeof(int);
        } else if(t == FLOAT) {
            dataSize = sizeof(float);
        } else {
            dataSize = sizeof(bool);
        }
        
        constValue = malloc(dataSize);
        memcpy(constValue, desc.value, dataSize);
    }
    ExpressionTree::freeHeap();
}

Expression::~Expression() {
    if(constValue) {
        free(constValue);
    }
    delete tree;
}

bool Expression::isConstant() {
    return isConst;
}

DataType Expression::getType() {
    return t;
}

void Expression::getValue(void *p) {
    size_t dataSize;
    if (t == INT) {
        dataSize = sizeof(int);
    } else if(t == FLOAT) {
        dataSize = sizeof(float);
    } else {
        dataSize = sizeof(bool);
    }
    
    if(isConst) {
        memcpy(p, constValue, dataSize);
        return;
    }
    
    ExpressionDesc desc = tree->evaluate();
    t = desc.type;
    
    memcpy(p, desc.value, dataSize);
    
    ExpressionTree::freeHeap();
}