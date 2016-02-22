//
//  Operator.h
//  AST
//
//  Created by Donald Pinckney on 4/3/15.
//  Copyright (c) 2015 donald. All rights reserved.
//

#ifndef AST_Operator_h
#define AST_Operator_h

#include "StringHelp.h"
#include <string>
#include <vector>
#include <functional>

namespace lemonscript_expressions {


template <typename T>
class Operator {
public:
    std::string pattern;
    int numArgs;
    bool associatesLeft;
    std::function<T (std::vector<T>)> f;
    
    Operator(const std::string &pa, int n, bool left, const std::function<T (std::vector<T>)> &func) :
    pattern(pa), numArgs(n), associatesLeft(left), f(func) { }
    
    
    // Not necessarily legit, but works for our simple operators
    std::vector<std::string> arguments(const std::string &s) const {
        std::function<std::string (std::string)> reverseFunc = associatesLeft ? reverse_c<std::string> : identity_c<std::string>;
        std::string removed = reverseFunc(s);
        
        std::string separator = reverseFunc(replaceAll(replaceAll(pattern, ".*", ""), "\\", ""));
        std::vector<std::string> parts;
        bool didFindAnyParts = false;
        
        std::string::size_type foundIndex = std::string::npos;
        while((foundIndex = removed.find(separator)) != std::string::npos && parts.size() < numArgs - 1) {
            StringRange range(0, int(foundIndex));
            parts.push_back(reverseFunc(substring(removed, range)));
            removed.erase(range.start, range.len + separator.size());
            
            didFindAnyParts = true;
        }
        
        std::string ending = reverseFunc(removed);
        if(!didFindAnyParts) {
            ending.erase(0, separator.size());
        } else {
//            ending.erase(0, separator.size()-1);
        }
//        ending = reverseFunc(ending);
        
        parts.push_back(ending);
        if(associatesLeft) {
            return reverse_c(parts);
        } else {
            return parts;
        }
    }
};


template <typename T>
bool operator==(const Operator<T> &lhs, const Operator<T> &rhs) {
    return lhs.pattern == rhs.pattern;
}

template <typename T>
bool operator!=(const Operator<T> &lhs, const Operator<T> &rhs) {
    return !(lhs == rhs);
}

    
}


#endif
