//
// Created by Ramadan on 4/22/2017.
//

#ifndef COMPILERPHASE1_PRODENGINE_H
#define COMPILERPHASE1_PRODENGINE_H

#include <bits/stdc++.h>
#include "ProdRulesParser.h"
#include "Expression.h"
using namespace std;
class ProdEngine {
public:
    ProdEngine(string filePath){
        table = new map<pair<NonTerminal*,Terminal*> , Expression*>();
        ProdRulesParser *parser = new ProdRulesParser(filePath);
        parser->parse();
        vector<Terminal*> *terminals = parser->getTerminals();
        vector<NonTerminal*> *nonTerminals = parser->getNonTerminals();
        parser->getStart()->addFollow(ProdRulesParser::getEndOfExp());
        for(NonTerminal* t : *nonTerminals){
            t->handleFirst();
            cout << "NonTerminal : " << t->getName() <<" First is : \n";
            for(Terminal *f : *(t->getFirst())){
                cout << f->getName() << " ";
            }
            cout << "\n";
        }
        for(NonTerminal* t : *nonTerminals){
            t->handleFollow();
            cout << "NonTerminal : "<< t->getName() <<" Follow is:" << "\n";
            for(Terminal* f : *(t->getFollow())){
                cout << f->getName() << " ";
            }
            cout << "\n";
        }

        ofstream tableOut;
        tableOut.open("C:\\CompilerPhase1\\predective_table.txt");

        for(NonTerminal* t : *nonTerminals){

            map<Terminal*,Expression*> *associatedMap = t->getNext();
            for(auto it : *associatedMap){
                table->insert({{t,it.first},it.second});
                tableOut << t->getName() << " " << it.first->getName() << " ";
                for(auto operand : it.second->getOperands()){
                    tableOut << operand->getName() << " ";
                }
                tableOut << "\n";
            }
        }


        start = parser->getStart();
        terminalsMap = parser->getTerminalsMap();
    }
    NonTerminal* getStart();
    map<pair<NonTerminal*,Terminal*> , Expression*> *getTable();
    map<string,Terminal*> getTerminalsMap();
private:
    map<pair<NonTerminal*,Terminal*> , Expression*> *table;
    NonTerminal* start;
    map<string,Terminal*> terminalsMap;
};


#endif //COMPILERPHASE1_PRODENGINE_H
