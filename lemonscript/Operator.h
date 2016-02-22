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

using namespace std;

namespace lemonscript_expressions {


template <typename T>
class Operator {
public:
    string pattern;
    int numArgs;
    bool associatesLeft;
    function<T (vector<T>)> f;
    
    Operator(const string &pa, int n, bool left, const function<T (vector<T>)> &func) :
    pattern(pa), numArgs(n), associatesLeft(left), f(func) { }
    
    
    // Not necessarily legit, but works for our simple operators
    vector<string> arguments(const string &s) const {
        function<string (string)> reverseFunc = associatesLeft ? reverse_c<string> : identity_c<string>;
        string removed = reverseFunc(s);
        
        string separator = reverseFunc(replaceAll(replaceAll(pattern, ".*", ""), "\\", ""));
        vector<string> parts;
        bool didFindAnyParts = false;
        
        string::size_type foundIndex = string::npos;
        while((foundIndex = removed.find(separator)) != string::npos && parts.size() < numArgs - 1) {
            StringRange range(0, int(foundIndex));
            parts.push_back(reverseFunc(substring(removed, range)));
            removed.erase(range.start, range.len + separator.size());
            
            didFindAnyParts = true;
        }
        
        string ending = reverseFunc(removed);
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
