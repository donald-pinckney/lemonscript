//
//  ASTNode.h
//  AST
//
//  Created by Donald Pinckney on 4/3/15.
//  Copyright (c) 2015 donald. All rights reserved.
//

#ifndef AST_ASTNode_h
#define AST_ASTNode_h

#include "Operator.h"
#include <vector>
#include <string>
#include <regex>

namespace lemonscript_expressions {


template <typename T>
class ASTNode {
public:
    Operator<T> op;
    ASTNode<T> *parent;
    std::vector<ASTNode<T> *> children;
    std::string text;
    
    
    ASTNode(const Operator<T> &o, ASTNode<T> *p, const std::vector<ASTNode<T> *> &ch, const std::string &t) : op(o), parent(p), text(t) {
        for(typename std::vector<ASTNode<T> *>::const_iterator it = ch.begin(); it != ch.end(); it++) {
            addChild(*it);
        }
    }
    
    void addChild(ASTNode<T> *c) {
        if(c) {
            children.push_back(c);
            c->parent = this;
        }
    }
    
    
    ~ASTNode() {
        for(typename std::vector<ASTNode<T> *>::iterator it = children.begin(); it != children.end(); it++) {
            delete *it;
        }
    }
    
    
    static ASTNode<T> * buildAST(const std::vector<Operator<T>> &ops, const std::string &s) {
        // Before normal operators are tested for, recursively find ( ) groupings
        std::string removedParens = replaceAll(s, " ", "");
        std::vector<ASTNode<T> *> parenNodes;
        int parenCount = 0;
        ParenResult parenResult = ParenResult::NoResult();
        while ((parenResult = firstParenMatch(removedParens)).hasMatch) {
            parenNodes.push_back(buildAST(ops, parenResult.inside.substring));
            removedParens.replace(parenResult.outside.start, parenResult.outside.len, "[" + std::to_string(parenCount) + "]");
            parenCount++;
        }
        
        
        
        
        for(int i = int(ops.size() - 1); i >= 0; i--) {
            Operator<T> o = ops[i];
            if(std::regex_match(removedParens, std::regex(o.pattern))) {
                // If its not the highest precedence operator (the atom)
                if(o != ops[0]) {
                    std::vector<std::string> args = o.arguments(removedParens);
                    std::vector<ASTNode<T> *> children;
                    for(int j = 0; j < args.size(); j++) {
                        std::string arg = args[j];
                        
                        
                        if (std::regex_match(arg, std::regex("\\[\\d+\\]"))) {
                            std::string numString = replaceAll(replaceAll(arg, "[", ""), "]", "");
                            children.push_back(parenNodes[stoi(numString)]);
                        } else {
                            
                            for(int k = 0; k < parenNodes.size(); k++) {
                                arg = std::regex_replace(arg, std::regex("\\["+ std::to_string(k) +"\\]"), "(" + parenNodes[k]->text + ")");
                            }

                            
                            children.push_back(buildAST(ops, arg));
                        }
                    }
                    
                    ASTNode<T> *node = new ASTNode<T>(o, NULL, children, removedParens);
                    return node;
                } else {
                    return new ASTNode<T>(o, NULL, {}, removedParens);
                }
            }
        }
        
        throw "invalid sentence";
    }
    
    
    
    std::set<std::string> uniqueVariables() const {
        std::set<std::string> vars;
        if(op.numArgs == 0) {
            vars.insert(text);
        }
        
        for(int i = 0; i < children.size(); i++) {
            std::set<std::string> childrenVars = children[i]->uniqueVariables();
            vars.insert(childrenVars.begin(), childrenVars.end());
        }
        return vars;
    }
    
    
    
    T evaluate(std::function<T(std::string)> vals) const {
        if(op.numArgs != 0) {
            std::vector<T> childResults;
            for(int i = 0; i < children.size(); i++) {
                childResults.push_back(children[i]->evaluate(vals));
            }
            return op.f(childResults);
        } else {
            T sub = vals(text);
            return op.f({sub});
        }
    }

};

}



#endif
