//
//  CppCommand.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/24/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include "CppCommand.h"

#include <strings.h>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <sstream>

#include "ParsingUtils.h"

using namespace std;

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

lemonscript::CppCommand::CppCommand(int l, const LemonScriptState &state, const std::string &commandStringInput) : Command(l, state) {
    std::string commandString = ParsingUtils::removeCommentFromLine(commandStringInput);
    
    string functionName;
    vector<void *> arguments;
    
    size_t colonIndex = commandString.find(":");
    functionName = commandString.substr(0, colonIndex);
    functionName = camelCase(functionName);
    
    vector<DataType> parameterTypes;
    
    if(colonIndex != string::npos) { // There are arguments
        string argumentsString = commandString.substr(colonIndex + 1);
        bool insideArgument = false;
        bool skipToComma = false;
        auto endIt = argumentsString.rbegin();
        for (auto it = argumentsString.rbegin(); it != argumentsString.rend(); ++it) {
            char c = *it;
            if(skipToComma && (c != ',')) {
                continue;
            } else if (skipToComma && (c == ',')) {
                skipToComma = false;
                continue;
            }
            
            if((insideArgument == false) && isArgumentChar(c)) { // end of a new argument
                endIt = it;
                insideArgument = true;
            }
            
            if(insideArgument && (isArgumentChar(c) == false)) { // start of argument
                auto startIt = it;
                string argumentString(endIt, startIt);
                reverse(argumentString.begin(), argumentString.end());
                
                skipToComma = true;
                insideArgument = false;
                
                if(argumentString == "false") {
                    parameterTypes.push_back(BOOLEAN);
                    arguments.push_back((void *)0);
                    isArgumentLiteral.push_back(true);
                } else if(argumentString == "true") {
                    parameterTypes.push_back(BOOLEAN);
                    arguments.push_back((void *)1);
                    isArgumentLiteral.push_back(true);
                } else {
                    // try to parse argument as an int
                    try {
                        if(argumentString.find(".") != string::npos) {
                            throw invalid_argument("ITS A FLOAT!");
                        }
                        int argVal = stoi(argumentString);
                        parameterTypes.push_back(INT);
                        arguments.push_back(reinterpret_cast<void *>(argVal));
                        isArgumentLiteral.push_back(true);
                        continue;
                    } catch (invalid_argument &err) {
                        
                    }
                    
                    
                    // try to parse argument as a float
                    try {
                        float argVal = stof(argumentString);
                        int tempArgVal = *((int *)&argVal);
                        parameterTypes.push_back(FLOAT);
                        arguments.push_back(reinterpret_cast<void *>(tempArgVal));
                        isArgumentLiteral.push_back(true);
                        continue;
                    } catch (invalid_argument &err) {
                        
                    }
                    
                    // otherwise it must be a variable!
                    void *address = state.addressOfVariable(argumentString);
                    if(address == NULL) {
                        throw "Line " + to_string(l) + ":\nUse of undeclared variable: " + argumentString;
                        return;
                    }

                    DataType type = state.typeOfVariable(argumentString);

                    parameterTypes.push_back(type);
                    arguments.push_back(address);
                    dependentVariables.push_back(address);
                    isArgumentLiteral.push_back(false);
                }
            }
        }
        
        

        
    }
    
    reverse(arguments.begin(), arguments.end());
    reverse(parameterTypes.begin(), parameterTypes.end());
    reverse(isArgumentLiteral.begin(), isArgumentLiteral.end());
    
    
    parameterValues = arguments;

    const AvailableCppCommandDeclaration *decl = state.lookupCommandDeclaration(functionName, parameterTypes);

    if(decl == NULL) {
        ostringstream tempStream;
        printParamTypes(parameterTypes, tempStream);
        
        throw "Line " + to_string(l) + ":\nNo matching function: " + functionName + "(" + tempStream.str() + ")";
    }
    
    declaration = decl;
    
    
}


#include "CppCommand_GENERATED.h"
