//
//  LemonScriptParser.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/30/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include "LemonScriptTokenizer.h"

using namespace::std;

// From http://stackoverflow.com/questions/10268872/c-fstream-function-that-reads-a-line-without-extracting
string peekLine(istream &is) {
    size_t len = is.tellg();
    
    string line;
    
    // Read line
    getline(is, line);
    
    // Return to position before "Read line".
    is.seekg(len , std::ios_base::beg);
    
    return line;
}

bool beginsWith(const string &x, const string &y) {
    return x.compare(0, y.length(), y) == 0;
}

bool isExecutableLine(const string &line) {
    for (auto it = line.begin(); it != line.end(); it++) {
        char c = *it;
        
        if(c == '/') {
            auto nextIt = it + 1;
            if (nextIt != line.end()) {
                char nextC = *nextIt;
                
                if(nextC == '/') {
                    return false;
                } else {
                    throw "Invalid token '/'";
                }
            } else {
                throw "Invalid token '/'";
            }
        }
        
        if(isalnum(c)) {
            return true;
        }
    }
    
    return false;
}


//LemonScriptTokenizer::LemonScriptTokenizer(const string &toParse) {
//    input = 
//    input.str(toParse);
//}

tuple<string, TokenType, int> LemonScriptTokenizer::nextToken() {
    
    string firstLine;
    getline(*input, firstLine);
    currentLine++;
    
    while(isExecutableLine(firstLine) == false) {
        getline(*input, firstLine);
        currentLine++;
    }
    
    
    // Now we have an executable line in firstLine
    // We now categorize firstLine
    int startLine = currentLine;
    bool isScoping = false;
    TokenType type;
    if(beginsWith(firstLine, "WHILE:")) {
        isScoping = true;
        type = WhileAlsoToken;
    } else if(beginsWith(firstLine, "LET ")) {
        type = LetToken;
    } else if(beginsWith(firstLine, "COMPLETE ALL:")) {
        isScoping = true;
        type = CompleteAllToken;
    } else if(beginsWith(firstLine, "COMPLETE ANY:")) {
        isScoping = true;
        type = CompleteAnyToken;
    } else if(beginsWith(firstLine, "IF:")) {
        isScoping = true;
        type = IfElseIfElseToken;
    } else if(beginsWith(firstLine, "NOT ")) {
        type = NotToken;
    } else {
        type = CppToken;
    }
    
    
    // Now we need to grab the following lines that belong
    ostringstream tempTokenStorage;
    if(!isScoping) {
        tempTokenStorage << firstLine;
    } else if(type == WhileAlsoToken) {
        while(true) {
            tempTokenStorage << firstLine << endl;
            
            string nextLine = peekLine(*input);
            if(!beginsWith(nextLine, "  ") && !beginsWith(nextLine, "ALSO:") && isExecutableLine(nextLine)) {
                break;
            }
            
            getline(*input, firstLine);
            currentLine++;
            
            
        }
    } else if(type == CompleteAllToken || type == CompleteAnyToken) {
        while(true) {
            tempTokenStorage << firstLine << endl;
            
            string nextLine = peekLine(*input);
            if(!beginsWith(nextLine, "  ") && isExecutableLine(nextLine)) {
                break;
            }
            
            getline(*input, firstLine);
            currentLine++;
        }
    } else if(type == IfElseIfElseToken) {
        while(true) {
            tempTokenStorage << firstLine << endl;
            
            string nextLine = peekLine(*input);
            if(!beginsWith(nextLine, "  ") && !beginsWith(nextLine, "THEN:") && !beginsWith(nextLine, "ELSE IF:") && !beginsWith(nextLine, "ELSE:") && isExecutableLine(nextLine)) {
                break;
            }
            
            
            getline(*input, firstLine);
            currentLine++;
        }
    }
    
    return make_tuple(tempTokenStorage.str(), type, startLine);
    
}