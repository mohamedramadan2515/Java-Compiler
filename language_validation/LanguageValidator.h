//
// Created by Ramadan on 4/24/2017.
//

#ifndef COMPILERPHASE1_LANGUAGEVALIDATOR_H
#define COMPILERPHASE1_LANGUAGEVALIDATOR_H

#include <bits/stdc++.h>
#include "../ProdRules/Terminal.h"
#include "../ProdRules/NonTerminal.h"

using namespace std;

class LanguageValidator {
public:
    LanguageValidator(map<pair<NonTerminal*,Terminal*>,Expression*> *table,string tokensFilePath,NonTerminal* start , map<string,Terminal*> terminalsMap){
        this->table = table;
        this->tokensFilePath = tokensFilePath;
        this->start = start;
        this->terminalsMap = terminalsMap;
    }
    void validate(ofstream &out);
private:
    map<pair<NonTerminal*,Terminal*>,Expression*> *table;
    string tokensFilePath;
    NonTerminal* start;
    map<string,Terminal*> terminalsMap;
    void printStack(stack<ProdOperand*> s,ofstream &out);
};


#endif //COMPILERPHASE1_LANGUAGEVALIDATOR_H
