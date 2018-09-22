//
// Created by Ramadan on 4/21/2017.
//

#include "NonTerminal.h"
#include "Expression.h"
#include "ProdRulesParser.h"

void NonTerminal::addExp(Expression *exp) {
    prodExps.push_back(exp);
}

set<Terminal *> *NonTerminal::getFirst() {
    if(!handledFirst){
        handleFirst();
    }
    set<Terminal*> *firstSym = new set<Terminal*>();
    for(auto it : *first){
        if(firstSym->find(it.first) != firstSym->end()){
            cout << this->getName() << " " << it.first->getName() << "\n";
            assert(false);
        }
        firstSym->insert(it.first);
    }
    return firstSym;
}

void NonTerminal::handleFirst() {
    if(!handledFirst){
        handledFirst = true;
        for(Expression* exp : prodExps){
            for(Terminal* t : *(exp->getFirst())){
                first->insert({t,exp});
            }
        }
    }
}

void NonTerminal::addAssociatedExp(Expression *exp) {
    associated_exps->insert(exp);
}

void NonTerminal::addFollow(Terminal *flw) {
    follow->insert(flw);
}

set<Terminal *> *NonTerminal::getFollow() {
    if(!handledFollow){
        handleFollow();
    }
    return  follow;
}

void NonTerminal::handleFollow() {
    if(!handledFollow){
        handledFollow = true;
        for(Expression* exp : *associated_exps){
            set<Terminal*> *expFollow = exp->getFollow(this);
            follow->insert(expFollow->begin() , expFollow->end());
        }
    }
}

map<Terminal *, Expression *> *NonTerminal::getNext() {
    if(!handledNext){
        handleNext();
    }
    return  nextMap;
}

void NonTerminal::handleNext() {
    if(!handledNext){
        handledNext = true;
        bool isEpsInFirst = false;
        // Add exp to all first Terminal except EPS
        for(pair<Terminal*,Expression*> firstCouple : *first){
            if(firstCouple.first == ProdRulesParser::getEps()){
                isEpsInFirst = true;
            }else{
                nextMap->insert(firstCouple);
            }
        }
        // IF there is Eps in first put all follow eps
        if(isEpsInFirst){
            Expression* epsExp = new Expression();
            epsExp->addOperand(ProdRulesParser::getEps());
            for(Terminal* followTerminal : *follow){
                if(nextMap->find(followTerminal) == nextMap->end()){
                    nextMap->insert({followTerminal,epsExp});
                }else {
                    assert(false);
                }
            }
        }else{// Else put all follow sync
            Terminal* syncTerminal = new Terminal("\\S");
            Expression * syncExp = new Expression();
            syncExp->addOperand(syncTerminal);
            for(Terminal* followTerminal : *follow){
                if(nextMap->find(followTerminal) == nextMap->end()){
                    nextMap->insert({followTerminal,syncExp});
                }
            }
        }
    }
}



