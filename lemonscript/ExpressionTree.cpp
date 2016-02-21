//
//  ExpressionTree.cpp
//  AST
//
//  Created by Donald Pinckney on 2/7/16.
//  Copyright © 2016 donald. All rights reserved.
//

#include "ExpressionTree.h"

#include <float.h>
#include <stdlib.h>

using namespace std;
using namespace lemonscript_expressions;


template <typename T>
void unaryAtomO(void *retPtr, vector<void *> args) {
    T ret = *((T *)args[0]);
    
    memcpy(retPtr, &ret, sizeof(T));
}

template <typename T>
void unaryNegO(void *retPtr, vector<void *> args) {
    T ret = !*((T *)args[0]);
    
    memcpy(retPtr, &ret, sizeof(T));
}

template <typename T>
void unaryMathNegO(void *retPtr, vector<void *> args) {
    T ret = -*((T *)args[0]);
    
    memcpy(retPtr, &ret, sizeof(T));
}

template <typename T>
void binaryExpO(void *retPtr, vector<void *> args) {
    T ret = T(powf(float(*((T *)args[0])), float(*((T *)args[1]))));
    
    memcpy(retPtr, &ret, sizeof(T));
}

template <typename T>
void binaryModO(void *retPtr, vector<void *> args) {
    T ret = *((T *)args[0]) % *((T *)args[1]);
    
    memcpy(retPtr, &ret, sizeof(T));
}

template <typename T>
void binaryDivO(void *retPtr, vector<void *> args) {
    T ret = *((T *)args[0]) / *((T *)args[1]);
    
    memcpy(retPtr, &ret, sizeof(T));
}

template <typename T>
void binaryAndO(void *retPtr, vector<void *> args) {
    T ret = *((T *)args[0]) && *((T *)args[1]);
    
    memcpy(retPtr, &ret, sizeof(T));
}

template <typename T>
void binaryMultO(void *retPtr, vector<void *> args) {
    T ret = *((T *)args[0]) * *((T *)args[1]);
    
    memcpy(retPtr, &ret, sizeof(T));
}

template <typename T>
void binarySubO(void *retPtr, vector<void *> args) {
    T ret = *((T *)args[0]) - *((T *)args[1]);
    
    memcpy(retPtr, &ret, sizeof(T));
}

template <typename T>
void binaryOrO(void *retPtr, vector<void *> args) {
    T ret = *((T *)args[0]) || *((T *)args[1]);
    
    memcpy(retPtr, &ret, sizeof(T));
}

template <typename T>
void binaryAddO(void *retPtr, vector<void *> args) {
    T ret = *((T *)args[0]) + *((T *)args[1]);
    
    memcpy(retPtr, &ret, sizeof(T));
}

template <typename T>
void binaryImpliesO(void *retPtr, vector<void *> args) {
    T ret = !*((T *)args[0]) || *((T *)args[1]);
    
    memcpy(retPtr, &ret, sizeof(T));
}


template <typename T>
void binaryEqualsO(void *retPtr, vector<void *> args) {
    bool ret = *((T *)args[0]) == *((T *)args[1]);
    
    memset(retPtr, ret, sizeof(bool));
}





template <typename T>
void binaryEqualsFLOAT_O(void *retPtr, vector<void *> args) {
//    T diff = fabs(*((T *)args[0]) - *((T *)args[1]));
//    bool ret = diff < 100 * FLT_EPSILON;
    
    // Code from: http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
    
    float A = *((T *)args[0]);
    float B = *((T *)args[1]);
    
    float maxDiff = 0.00001;
    float maxRelDiff = 0.00001;
    
    // Check if the numbers are really close -- needed
    // when comparing numbers near zero.
    float diff = fabs(A - B);
    if (diff <= maxDiff) {
        memset(retPtr, true, sizeof(bool));
        return;
    }
    
    
    A = fabs(A);
    B = fabs(B);
    float largest = (B > A) ? B : A;
    bool ret;

    if (diff <= largest * maxRelDiff) {
        ret = true;
    } else {
        ret = false;
    }
    
    memset(retPtr, ret, sizeof(bool));
}

struct OperatorType {
    DataType retType;
    vector<DataType> paramTypes;
    function<void(void *retPtr, vector<void *> argumentPtrs)> func;
    
    OperatorType(DataType rt, const vector<DataType> &pt, function<void(void *retPtr, vector<void *> argumentPtrs)> f) : retType(rt), paramTypes(pt), func(f) { }
};


function<ExpressionDesc(vector<ExpressionDesc>)> operatorResolve(vector<OperatorType> operatorTypes) {
    return [operatorTypes] (vector<ExpressionDesc> argumentDescriptions) {
        vector<DataType> argumentTypes;
        bool areAllConst = true;
        for (auto it = argumentDescriptions.begin(); it != argumentDescriptions.end(); it++) {
            argumentTypes.push_back(it->type);
            if (it->isConst == false) {
                areAllConst = false;
            }
        }
        
        
        for (int i = 0; i < operatorTypes.size(); i++) {
            OperatorType opType = operatorTypes[i];
            
            if(opType.paramTypes == argumentTypes) {
                
                DataType type = opType.retType;
                
                function<void(void *, vector<void *>)> f = opType.func;
                
                vector<void *> arguments;
                for (int j = 0; j < argumentDescriptions.size(); j++) {
                    ExpressionDesc argDesc = argumentDescriptions[j];
                    arguments.push_back(argDesc.value);
                }
                
                
                void *retVal;
                if(type == INT) {
                    retVal = ExpressionTree::alloc<int>();
                } else if(type == FLOAT) {
                    retVal = ExpressionTree::alloc<float>();
                } else {
                    retVal = ExpressionTree::alloc<bool>();
                }
                
                f(retVal, arguments);                
                
                ExpressionDesc desc(opType.retType, areAllConst, retVal);

                
                return desc;
            }
        }
        
#warning TODO: Give better error message here.
        throw "Invalid arguments.";
    };
}

vector<OperatorType> genericOperatorTypes(vector<DataType> Ts, vector<function<void(void *retPtr, vector<void *> argumentPtrs)>> funcs, int airity) { // Creates operators of the form T x T x ... x T -> T, which covers almost all cases
    vector<OperatorType> operatorTypes;
    
    int i = 0;
    for (auto it = Ts.begin(); it != Ts.end(); it++) {
        DataType T = *it;
        
        operatorTypes.push_back(OperatorType(T, vector<DataType>(airity, T), funcs[i]));
        i++;
    }
    return operatorTypes;
}

vector<OperatorType> genericOperatorTypesOtherReturn(vector<DataType> Ts, vector<function<void(void *retPtr, vector<void *> argumentPtrs)>> funcs, DataType U, int airity) { // Creates operators of the form T x T x ... x T -> U, useful for ==
    vector<OperatorType> operatorTypes;
    
    int i = 0;
    for (auto it = Ts.begin(); it != Ts.end(); it++) {
        DataType T = *it;
        operatorTypes.push_back(OperatorType(U, vector<DataType>(airity, T), funcs[i]));
        i++;
    }
    return operatorTypes;
}

const Operator<ExpressionDesc> DataType_atomO(".*", 0, true, operatorResolve(genericOperatorTypes({INT,FLOAT,BOOLEAN}, {unaryAtomO<int>, unaryAtomO<float>, unaryAtomO<bool>}, 1)));
const Operator<ExpressionDesc> DataType_unaryNegO("!.*", 1, true, operatorResolve(genericOperatorTypes({BOOLEAN}, {unaryNegO<bool>}, 1)));
const Operator<ExpressionDesc> DataType_unaryMathNegO("-.*", 1, true, operatorResolve(genericOperatorTypes({INT,FLOAT}, {unaryMathNegO<int>, unaryMathNegO<float>}, 1)));

const Operator<ExpressionDesc> DataType_expO(".*\\^.*", 2, true, operatorResolve(genericOperatorTypes({INT,FLOAT}, {binaryExpO<int>, binaryExpO<float>}, 2)));

const Operator<ExpressionDesc> DataType_modO(".*%.*", 2, true, operatorResolve(genericOperatorTypes({INT}, {binaryModO<int>}, 2)));
const Operator<ExpressionDesc> DataType_divO(".*/.*", 2, true, operatorResolve(genericOperatorTypes({INT,FLOAT}, {binaryDivO<int>, binaryDivO<float>}, 2)));
const Operator<ExpressionDesc> DataType_andO(".*&&.*", 2, true, operatorResolve(genericOperatorTypes({BOOLEAN}, {binaryAndO<bool>}, 2)));
const Operator<ExpressionDesc> DataType_multO(".*\\*.*", 2, true, operatorResolve(genericOperatorTypes({INT,FLOAT}, {binaryMultO<int>, binaryMultO<float>}, 2)));

const Operator<ExpressionDesc> DataType_subO(".*-.*", 2, true, operatorResolve(genericOperatorTypes({INT,FLOAT}, {binarySubO<int>, binarySubO<float>}, 2)));
const Operator<ExpressionDesc> DataType_orO(".*\\|\\|.*", 2, true, operatorResolve(genericOperatorTypes({BOOLEAN}, {binaryOrO<bool>}, 2)));
const Operator<ExpressionDesc> DataType_addO(".*\\+.*", 2, true, operatorResolve(genericOperatorTypes({INT,FLOAT}, {binaryAddO<int>, binaryAddO<float>}, 2)));

const Operator<ExpressionDesc> DataType_impliesO(".*=>.*", 2, true, operatorResolve(genericOperatorTypes({BOOLEAN}, {binaryImpliesO<bool>}, 2)));

const Operator<ExpressionDesc> DataType_equalsO(".*==.*", 2, true, operatorResolve(genericOperatorTypesOtherReturn({INT,FLOAT,BOOLEAN}, {binaryEqualsO<int>, binaryEqualsFLOAT_O<float>, binaryEqualsO<bool>}, BOOLEAN, 2)));







const vector<Operator<ExpressionDesc>> DATA_TYPE_OPERATORS = {DataType_atomO, DataType_unaryNegO, DataType_unaryMathNegO, DataType_expO, DataType_modO, DataType_divO, DataType_andO, DataType_multO, DataType_subO, DataType_orO, DataType_addO, DataType_impliesO, DataType_equalsO};

vector<void *> ExpressionTree::evaluationHeap;

ExpressionTree::ExpressionTree(const string &s, function<ExpressionDesc(string)> subs) : descriptionTree(ASTNode<ExpressionDesc>::buildAST(DATA_TYPE_OPERATORS, s)), descriptionSubstitutions(subs), sentenceText(s) { }


ExpressionDesc ExpressionTree::evaluate() const {
    ExpressionDesc retVal = descriptionTree->evaluate(descriptionSubstitutions);
        
    return retVal;
}


void ExpressionTree::freeHeap() {
    for (auto it = evaluationHeap.begin(); it != evaluationHeap.end(); it++) {
        free(*it);
    }
    
    evaluationHeap.clear();
}


ExpressionTree::~ExpressionTree() {
    delete descriptionTree;
}