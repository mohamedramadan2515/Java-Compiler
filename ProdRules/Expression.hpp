//
// Created by Ramadan on 4/21/2017.
//

#ifndef COMPILERPHASE1_EXPRESSION_H
#define COMPILERPHASE1_EXPRESSION_H

#include <bits/stdc++.h>
#include <vector>
#include "ProdOperand.hpp"
#include "Terminal.hpp"



using namespace std;

class NonTerminal;

class Expression {
public:
    void addOperand(ProdOperand *operand);
    void addLHS(NonTerminal* LHS);
    set<Terminal*> *getFirst();
    set<Terminal*> *getFollow(NonTerminal* nonTerminal);
    vector<ProdOperand *> getOperands();
private:
    NonTerminal* associatedLHS;
    vector<ProdOperand *> expression;
};


#endif //COMPILERPHASE1_EXPRESSION_H
