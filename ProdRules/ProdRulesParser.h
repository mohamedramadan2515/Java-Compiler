//
// Created by Ramadan on 4/21/2017.
//

#ifndef COMPILERPHASE1_PRODRULESPARSER_H
#define COMPILERPHASE1_PRODRULESPARSER_H

#include <iostream>
#include <bits/stdc++.h>
#include "Terminal.h"
#include "NonTerminal.h"

using namespace std;

class ProdRulesParser {
public :
    ProdRulesParser(string filePath){
        this->filePath = filePath;
        lastNonTerminal = NULL;
        terminalsMap["\\L"] = epsilon;
        terminalsMap["$"] = endOfExp;
    }
    void parse();
    vector<Terminal*> *getTerminals();
    vector<NonTerminal*> *getNonTerminals();
    map<string,Terminal*> getTerminalsMap();
    NonTerminal* getStart();
    static Terminal* getEps(){
        return epsilon;
    }
    static Terminal* getEndOfExp(){
        return  endOfExp;
    }
private:
    string filePath;
    map<string,NonTerminal*> nonTerminalsMap;
    map<string,Terminal*> terminalsMap;
    vector<Terminal*> terminals;
    vector<NonTerminal*> nonTerminals;
    NonTerminal *lastNonTerminal;
    void handleInputLine(string line);
    bool isNewProd(string line);
    NonTerminal* start;
    static Terminal* epsilon;
    static Terminal* endOfExp;

    NonTerminal* handleLHS( string &line) ;

    void handleRHS(string basic_string, NonTerminal *pTerminal);

    void addExpressions(string basic_string, NonTerminal *pTerminal);

    void convertStrtoExp(string basic_string, NonTerminal *pTerminal);

    int handleTerminal( string &expString, int idx, Expression *exp) ;

    int handleNonTerminal( string &expString, int idx, Expression *exp) ;
};


#endif //COMPILERPHASE1_PRODRULESPARSER_H
