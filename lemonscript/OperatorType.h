//
//  OperatorType.hpp
//  lemonscript
//
//  Created by Donald Pinckney on 2/28/16.
//  Copyright © 2016 Donald Pinckney. All rights reserved.
//

#ifndef OperatorType_hpp
#define OperatorType_hpp

#include <stdio.h>

#include <vector>
#include <functional>
#include <string>

#include "expressions.h"

#include "AvailableCppCommandDeclaration.h"

struct lemonscript_expressions::TypeSpecification {
    std::vector<lemonscript::DataType> inputTypes;
    lemonscript::DataType returnType;
    std::function<int32_t (std::vector<int32_t>)> func;
};

class lemonscript_expressions::OperatorType {
    
public:
    
    bool isIdentityOperator; // True iff (i)T = T and (i)x = x
    
    std::string operatorText;
    
    std::vector<lemonscript_expressions::TypeSpecification> specifications;
    
    static OperatorType identity() {
        std::vector<TypeSpecification> specs;
        std::vector<lemonscript::DataType> types = {lemonscript::DataType::BOOLEAN, lemonscript::DataType::INT, lemonscript::DataType::FLOAT};
        for(auto it = types.begin(); it != types.end(); ++it) {
            lemonscript::DataType t = *it;
            TypeSpecification spec;
            spec.inputTypes = {t};
            spec.returnType = t;
            spec.func = [] (std::vector<int32_t> xs) { return xs[0]; };
            specs.push_back(spec);
        }
        OperatorType opType;
        opType.isIdentityOperator = true;
        opType.specifications = specs;
        opType.operatorText = "i";
        
        return opType;
    }
};

std::ostream & operator<<(std::ostream &o, lemonscript_expressions::OperatorType opType);

#endif /* OperatorType_hpp */
