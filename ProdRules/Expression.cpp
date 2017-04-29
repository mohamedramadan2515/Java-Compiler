//
// Created by Ramadan on 4/21/2017.
//

#include "Expression.h"
#include "NonTerminal.h"
#include "ProdRulesParser.h"

void Expression::addOperand(ProdOperand *operand) {
    expression.push_back(operand);
}

set<Terminal *> *Expression::getFirst() {
    set<Terminal*> *first = new set<Terminal*>();
    bool deleteEps = false;
    for(ProdOperand *operand : expression){
        if(Terminal* v = dynamic_cast<Terminal*>(operand)){
            first->insert((Terminal*)operand);
            break;
        }else{
            NonTerminal* nonTerminal = (NonTerminal*) operand;
            set<Terminal*> *nonTerminalFirst = nonTerminal->getFirst();
            first->insert(nonTerminalFirst->begin(),nonTerminalFirst->end());
            if(nonTerminalFirst->find(ProdRulesParser::getEps()) == nonTerminalFirst->end()){
                deleteEps = true;
                break;
            }
        }
    }
    if(deleteEps)
        first->erase(ProdRulesParser::getEps());
    return  first;
}

set<Terminal*> *Expression::getFollow(NonTerminal *nonTerminal) {
    set<Terminal*> *follow = new set<Terminal*>();
    for(int i = 0 ; i < expression.size();i++){
        ProdOperand* operand = expression[i];
        if(NonTerminal* v = dynamic_cast<NonTerminal*>(operand)){
            NonTerminal* op = (NonTerminal*)operand;
            if(op == nonTerminal){
                if(i != expression.size()-1) {//not last
                    Expression *newExp = new Expression();
                    for (int j = i + 1; j < expression.size(); j++) {
                        newExp->addOperand(expression[j]);
                    }
                    set<Terminal*> *newExpFirst = newExp->getFirst();
                    follow->insert(newExpFirst->begin(),newExpFirst->end());
                    follow->erase(ProdRulesParser::getEps());
                    if(newExpFirst->find(ProdRulesParser::getEps()) != newExpFirst->end()){
                        if(nonTerminal != associatedLHS){
                            set<Terminal*> *associatedLHSFollow = associatedLHS->getFollow();
                            follow->insert(associatedLHSFollow->begin(),associatedLHSFollow->end());
                        }
                    }
                }else{
                    if(nonTerminal != associatedLHS){
                        set<Terminal*> *associatedLHSFollow = associatedLHS->getFollow();
                        follow->insert(associatedLHSFollow->begin(),associatedLHSFollow->end());
                    }
                }
            }
        }
    }
    return  follow;
}

void Expression::addLHS(NonTerminal *LHS) {
    this->associatedLHS = LHS;
}

vector<ProdOperand *> Expression::getOperands() {
    return  expression;
}


