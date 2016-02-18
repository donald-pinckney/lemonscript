//
//  StringHelp.cpp
//  AST
//
//  Created by Donald Pinckney on 4/3/15.
//  Copyright (c) 2015 donald. All rights reserved.
//

#include "StringHelp.h"

using namespace lemonscript_expressions;

ParenResult lemonscript_expressions::firstParenMatch(string s) {
    int i = 0;
    int start = -1;
    int depthCount = 0;
    int end = int(s.length());
    
    while(i != end) {
        char c = s[i];
        if(c == '(') {
            if(depthCount == 0) {
                start = i;
            }
            
            depthCount++;
        } else if(c == ')') {
            depthCount--;
        }
        
        if(depthCount == 0 && start != -1) {
            lemonscript_expressions::StringResult outside(s, start, i + 1);
            lemonscript_expressions::StringResult inside(s, start + 1, i);
            return lemonscript_expressions::ParenResult(inside, outside);
        }
        
        i++;
    }
    
    return lemonscript_expressions::ParenResult::NoResult();
}


string lemonscript_expressions::replaceAll(const string &str, const string &from, const string &to) {
    if(from.empty())
        return str;
    
    string ret = str;
    
    size_t start_pos = 0;
    while((start_pos = ret.find(from, start_pos)) != string::npos) {
        ret.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
    
    return ret;
}


string lemonscript_expressions::substring(const string &s, const lemonscript_expressions::StringRange &r) {
    return s.substr(r.start, r.len);
}


ParenResult lemonscript_expressions::ParenResult::NoResult() {
    ParenResult r(StringResult("", 0, 0), StringResult("", 0, 0));
    r.hasMatch = false;
    return r;
}

