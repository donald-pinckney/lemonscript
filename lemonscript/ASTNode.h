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
#include <map>

using namespace std;

namespace lemonscript_expressions {


template <typename T>
class ASTNode {
public:
    Operator<T> op;
    ASTNode<T> *parent;
    vector<ASTNode<T> *> children;
    string text;
    
    
    ASTNode(const Operator<T> &o, ASTNode<T> *p, const vector<ASTNode<T> *> &ch, const string &t) : op(o), parent(p), text(t) {
        for(typename vector<ASTNode<T> *>::const_iterator it = ch.begin(); it != ch.end(); it++) {
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
        for(typename vector<ASTNode<T> *>::iterator it = children.begin(); it != children.end(); it++) {
            delete *it;
        }
    }
    
    
    static ASTNode<T> * buildAST(const vector<Operator<T>> &ops, const string &s) {
        // Before normal operators are tested for, recursively find ( ) groupings
        string removedParens = replaceAll(s, " ", "");
        vector<ASTNode<T> *> parenNodes;
        int parenCount = 0;
        ParenResult parenResult = ParenResult::NoResult();
        while ((parenResult = firstParenMatch(removedParens)).hasMatch) {
            parenNodes.push_back(buildAST(ops, parenResult.inside.substring));
            removedParens.replace(parenResult.outside.start, parenResult.outside.len, "[" + to_string(parenCount) + "]");
            parenCount++;
        }
        
        
        
        
        for(int i = int(ops.size() - 1); i >= 0; i--) {
            Operator<T> o = ops[i];
            if(regex_match(removedParens, regex(o.pattern))) {
                // If its not the highest precedence operator (the atom)
                if(o != ops[0]) {
                    vector<string> args = o.arguments(removedParens);
                    vector<ASTNode<T> *> children;
                    for(int j = 0; j < args.size(); j++) {
                        string arg = args[j];
                        
                        
                        if (regex_match(arg, regex("\\[\\d+\\]"))) {
                            string numString = replaceAll(replaceAll(arg, "[", ""), "]", "");
                            children.push_back(parenNodes[stoi(numString)]);
                        } else {
                            
                            for(int k = 0; k < parenNodes.size(); k++) {
                                arg = regex_replace(arg, regex("\\["+ to_string(k) +"\\]"), "(" + parenNodes[k]->text + ")");
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
    
    
    
    set<string> uniqueVariables() const {
        set<string> vars;
        if(op.numArgs == 0) {
            vars.insert(text);
        }
        
        for(int i = 0; i < children.size(); i++) {
            set<string> childrenVars = children[i]->uniqueVariables();
            vars.insert(childrenVars.begin(), childrenVars.end());
        }
        return vars;
    }
    
    
    
    T evaluate(function<T(string)> vals) const {
        if(op.numArgs != 0) {
            vector<T> childResults;
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
