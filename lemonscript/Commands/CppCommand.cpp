//
//  CppCommand.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include "CppCommand.h"
#include "Expression.h"

#include <strings.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "ParsingUtils.h"

using namespace std;

using namespace lemonscript_expressions;

void printParamTypes(const vector<DataType> &types, ostream &stream) {
    
    for (auto it = types.rbegin(); it != types.rend(); ++it) {
        string text;
        switch (*it) {
            case INT:
                text = "int";
                break;
                
            case FLOAT:
                text = "float";
                break;
                
            case BOOLEAN:
                text = "bool";
                break;
                
            default:
                break;
        }
        
        stream << text;
        if((it + 1) != types.rend()) {
            stream << ", ";
        }
    }
}

bool isArgumentChar(char c) {
    return isalnum(c) || c == '_' || c == '-' || c == '.';
}

string camelCase(const string &s) {
    // s = "cat"
    char *resultTemp = new char[s.length() + 1];
    bzero(resultTemp, sizeof(char) * (s.length() + 1));
    
    int resultIndex = 0;
    bool insideWord = false;
    for (auto it = s.begin(); it != s.end(); ++it) {
        char c = *it;
        
        if(insideWord && isalnum(c)) {
            resultTemp[resultIndex++] = c;
        }
        
        if((insideWord == false) && isalnum(c)) {
            resultTemp[resultIndex++] = toupper(c);
            insideWord = true;
        }
        

        
        if(insideWord && (isalnum(c) == false)) {
            insideWord = false;
        }
    }
    
    return string(resultTemp);
}



inline bool IsSpace (char c) { return c == ' '; }

lemonscript::CppCommand::CppCommand(int l, LemonScriptState *state, const std::string &commandStringInput) : Command(l, state) {
    std::string commandString = ParsingUtils::removeCommentFromLine(commandStringInput);
    
    string functionName;
    vector<void *> arguments;
    
    size_t colonIndex = commandString.find(":");
    functionName = commandString.substr(0, colonIndex);
    functionName = camelCase(functionName);
    
    vector<DataType> parameterTypes;
    
    if(colonIndex != string::npos) { // There are arguments
        string argumentsString = commandString.substr(colonIndex + 1);
        
        // Remove whitespace in the string, make the parsing a bit easier
        argumentsString.erase(std::remove_if(argumentsString.begin(), argumentsString.end(), IsSpace), argumentsString.end());
        
        auto endOfArgIt = argumentsString.rbegin();

        for (auto it = argumentsString.rbegin(); it != argumentsString.rend(); ++it) {
            
            char c = *it;
            
            auto startOfArgIt = it;
            auto newEndOfArgIt = it;
            if(c == ':') { // Then we want to eat up the prefix to the argument
                while (true) {
                    char d = *it;
                    if(d == ',') {
                        newEndOfArgIt = it + 1;
                        break;
                    }
                    ++it;
                }
            }
            
            if(c == ':' || c == ',' || it + 1 == argumentsString.rend()) { // Then we reached the prefix before the argument expression
                if(it + 1 == argumentsString.rend()) {
                    ++startOfArgIt;
                }
                
                if(c == ',') {
                    ++newEndOfArgIt;
                }
                
                string argumentString(endOfArgIt, startOfArgIt);
                reverse(argumentString.begin(), argumentString.end());
                
                cout << argumentString << endl;
                
                endOfArgIt = newEndOfArgIt;
                
                
                lemonscript_expressions::Expression *expr = new lemonscript_expressions::Expression(argumentString, state, l);
                DataType type = expr->getType();
                
                parameterTypes.push_back(type);

                
                if(expr->isConstant()) {
                    if(type == INT) {
                        int val;
                        expr->getValue(&val);
                        arguments.push_back(reinterpret_cast<void *>(val));
                    } else if(type == FLOAT) {
                        float val;
                        expr->getValue(&val);
                        int tempArgVal = *((int *)&val);
                        arguments.push_back(reinterpret_cast<void *>(tempArgVal));
                    } else {
                        bool val;
                        expr->getValue(&val);
                        arguments.push_back((void *)val);
                    }
                    
                    
                    isArgumentLiteral.push_back(true);
                } else {
                    isArgumentLiteral.push_back(false);
                    arguments.push_back(expr);

                }
            }
            
            
        }
        
        

        
    }
    
    reverse(arguments.begin(), arguments.end());
    reverse(parameterTypes.begin(), parameterTypes.end());
    reverse(isArgumentLiteral.begin(), isArgumentLiteral.end());
    
    
    parameterValues = arguments;

    const AvailableCppCommandDeclaration *decl = state->lookupCommandDeclaration(functionName, parameterTypes);

    if(decl == NULL) {
        ostringstream tempStream;
        printParamTypes(parameterTypes, tempStream);
        
        throw "Line " + to_string(l) + ":\nNo matching function: " + functionName + "(" + tempStream.str() + ")";
    }
    
    declaration = decl;
    
    
}


#include "CppCommand_GENERATED.h"
