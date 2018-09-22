//
// Created by Ramadan on 4/21/2017.
//

#ifndef COMPILERPHASE1_NONTERMINAL_H
#define COMPILERPHASE1_NONTERMINAL_H


#include "ProdOperand.h"

#include "Terminal.h"
#include <bits/stdc++.h>

using namespace std;

class Expression;

class NonTerminal : public ProdOperand {
public:
    NonTerminal(string name) : ProdOperand(name) {
        handledFirst = handledFollow =handledNext= false;
        first = new set<pair<Terminal *, Expression *>>();
        follow = new set<Terminal *>();
        associated_exps = new set<Expression *>();
        nextMap = new map<Terminal*,Expression*>();
    }

    void addExp(Expression *exp);//as prodRule
    void handleFirst();

    void addAssociatedExp(Expression *exp);

    void addFollow(Terminal *flw);

    void handleFollow();
    void handleNext();
    set<Terminal *> *getFollow();

    set<Terminal *> *getFirst();

    map<Terminal*,Expression*> *getNext();
private:
    vector<Expression *> prodExps;
    set<Expression *> *associated_exps;
    set<pair<Terminal *, Expression *>> *first;
    map<Terminal*,Expression*> *nextMap;
    set<Terminal *> *follow;
    bool handledFirst;
    bool handledFollow;
    bool handledNext;
};


#endif //COMPILERPHASE1_NONTERMINAL_H
