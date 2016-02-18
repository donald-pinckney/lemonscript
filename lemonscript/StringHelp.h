//
//  StringHelp.h
//  AST
//
//  Created by Donald Pinckney on 4/3/15.
//  Copyright (c) 2015 donald. All rights reserved.
//

#ifndef __AST__StringHelp__
#define __AST__StringHelp__

#include <stdio.h>
#include <string>

using namespace std;


namespace lemonscript_expressions {


class StringRange {
public:
    int start;
    int end;
    int len;
    StringRange(int s, int e) : start(s), end(e), len(e - s) { }
};



class StringResult {
    
public:
    int start;
    int end;
    string original;
    string substring;
    int len;
    StringResult(const string &o, int s, int e) : start(s), end(e), original(o), substring(original.substr(s, e - s)), len(e - s) { }
};

class ParenResult {
    
public:
    StringResult inside;
    StringResult outside;
    bool hasMatch;
    ParenResult(const StringResult &i, const StringResult &o) : inside(i), outside(o), hasMatch(true) { }
    static ParenResult NoResult();
};



template <typename T>
T reverse_c(const T &s) {
    T ret = s;
    reverse(ret.begin(), ret.end());
    return ret;
}

template <typename T>
T identity_c(const T &s) {
    return s;
}


string substring(const string &s, const StringRange &r);
ParenResult firstParenMatch(string s);
string replaceAll(const string &str, const string &from, const string &to);

}


#endif /* defined(__AST__StringHelp__) */
