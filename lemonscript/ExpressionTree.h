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

#include "ASTNode.h"
#include "AvailableCppCommandDeclaration.h"

using namespace std;

namespace lemonscript_expressions {

struct ExpressionDesc {
    DataType type;
    bool isConst;

    void *value;
    
    ExpressionDesc(DataType t, bool isC, void *v) : type(t), isConst(isC), value(v) { };
};


class ExpressionTree {
    ASTNode<ExpressionDesc> *descriptionTree;
    function<ExpressionDesc(string)> descriptionSubstitutions;

    static vector<void *> evaluationHeap;

    string sentenceText;
    
    
public:
    
    ExpressionTree(const string &s, function<ExpressionDesc(string)> descSubs);
    
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
