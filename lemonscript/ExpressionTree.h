//
//  PropositionalLogic.h
//  AST
//
//  Created by Donald Pinckney on 4/3/15.
//  Copyright (c) 2015 donald. All rights reserved.
//

#ifndef __AST__ExpressionTree__
#define __AST__ExpressionTree__

#include <stdio.h>
#include <set>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <string>

#include "ASTNode.h"
#include "AvailableCppCommandDeclaration.h"

namespace lemonscript_expressions {

struct ExpressionDesc {
    DataType type;
    bool isConst;

    void *value;
    
    ExpressionDesc(DataType t, bool isC, void *v) : type(t), isConst(isC), value(v) { };
};


class ExpressionTree {
    ASTNode<ExpressionDesc> *descriptionTree;
    std::function<ExpressionDesc(std::string)> descriptionSubstitutions;

    static std::vector<void *> evaluationHeap;

    std::string sentenceText;
    
    
public:
    
    ExpressionTree(const std::string &s, std::function<ExpressionDesc(std::string)> descSubs);
    
    ExpressionDesc evaluate() const;
    
    template<typename T>
    static T *alloc() {
        size_t memSize = sizeof(T);
        T *mem = (T *)malloc(memSize);
        evaluationHeap.push_back(mem);
        return mem;
    }

    static void freeHeap();
    
    ~ExpressionTree();
};
    
}


#endif /* defined(__AST__ExpressionTree__) */
