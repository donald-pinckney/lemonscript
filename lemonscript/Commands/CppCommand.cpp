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
#include <fstream>
#include <sstream>
#include <algorithm>

#include "ParsingUtils.h"

using namespace std;

using namespace lemonscript_expressions;
using lemonscript::DataType;

void printParamTypes(const vector<DataType> &types, ostream &stream) {
    
    for (auto it = types.rbegin(); it != types.rend(); ++it) {
        string text;
        switch (*it) {
            case DataType::INT:
                text = "int";
                break;
                
            case DataType::FLOAT:
                text = "float";
                break;
                
            case DataType::BOOLEAN:
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
    functionName = ParsingUtils::trimWhitespace(functionName);
    
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
                    if(d == ',' || it + 1 == argumentsString.rend()) {
                        newEndOfArgIt = it + 1;
                        break;
                    }
                    ++it;
                }
            }
            
            if(c == ':' || c == ',' || it + 1 == argumentsString.rend()) { // Then we reached the prefix before the argument expression
                if(it == argumentsString.rend()) {
                    //break;
                }
                
                if(startOfArgIt + 1 == argumentsString.rend()) {
                    startOfArgIt = argumentsString.rend();
                }
                
                if(c == ',') {
                    ++newEndOfArgIt;
                }
                
                string argumentString(endOfArgIt, startOfArgIt);
                reverse(argumentString.begin(), argumentString.end());
                                
                endOfArgIt = newEndOfArgIt;
              
                
                
                if(argumentString == "false") {
                    parameterTypes.push_back(DataType::BOOLEAN);
                    arguments.push_back((void *)0);
                    isArgumentLiteral.push_back(true);
                } else if(argumentString == "true") {
                    parameterTypes.push_back(DataType::BOOLEAN);
                    arguments.push_back((void *)1);
                    isArgumentLiteral.push_back(true);
                } else {
                    // try to parse argument as an int
                    try {
                        if(argumentString.find(".") != string::npos) {
                            throw invalid_argument("ITS A FLOAT!");
                        }
                        int argVal = stoi(argumentString);
                        parameterTypes.push_back(DataType::INT);
                        arguments.push_back(reinterpret_cast<void *>(argVal));
                        isArgumentLiteral.push_back(true);
                        continue;
                    } catch (invalid_argument &err) {
                        
                    }
                    
                    
                    // try to parse argument as a float
                    try {
                        float argVal = stof(argumentString);
                        int tempArgVal = *((int *)&argVal);
                        parameterTypes.push_back(DataType::FLOAT);
                        arguments.push_back(reinterpret_cast<void *>(tempArgVal));
                        isArgumentLiteral.push_back(true);
                        continue;
                    } catch (invalid_argument &err) {
                        
                    }
                    
                    throw "Expressions unsupported in stable-v0.1";
                    
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

lemonscript::CppCommand::~CppCommand() {
    for (int i = 0; i < parameterValues.size(); i++) {
        if(isArgumentLiteral[i] == false) {
            lemonscript_expressions::Expression *expr = (lemonscript_expressions::Expression *)parameterValues[i];
            delete expr;
        }
    }
}


#include "CppCommand_GENERATED.h"
