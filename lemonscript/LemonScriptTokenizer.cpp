//
//  LemonScriptParser.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/30/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include "LemonScriptTokenizer.h"

#include <tuple>

#include "ParsingUtils.h"

using namespace std;
using namespace ParsingUtils;




tuple<string, TokenType, int> LemonScriptTokenizer::nextToken() {
    
    string firstLine;
    getline(*input, firstLine);
    if(input->eof() && firstLine.length() == 0) {
        return make_tuple("", NOT_A_TOKEN, -1);
    }
    
    currentLine++;
    
    while(isExecutableLine(firstLine) == false) {
        getline(*input, firstLine);
        if(input->eof() && firstLine.length() == 0) {
            return make_tuple("", NOT_A_TOKEN, -1);
        }
        
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