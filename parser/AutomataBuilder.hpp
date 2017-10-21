//
// Created by Admin on 3/21/2017.
//

#ifndef COMPILERPHASE1_AUTOMATABUILDER_H
#define COMPILERPHASE1_AUTOMATABUILDER_H

#include <string>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <ctype.h>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <stack>
#include "../utils/string_utils.hpp"
#include "../automata/EmptyAutomata.hpp"
#include "../utils/Constants.hpp"
#include "../automata/Automata.hpp"

using namespace std;

class AutomataBuilder {
public:

    AutomataBuilder() {
        typeMapping = new map<int, string>();
    }

    Automata *build(string filePath);

private:
    map<string, string> definitions;
    vector<string> definitionsIds;
    map<char, int> operationPrecedence = {{'|', 1},
                                          {' ', 2},
                                          {'*', 3},
                                          {'+', 3}};

    set<char> allPossibleInputs;
public:
    set<char> *getAllPossibleInputs();

    map<int, string> *getTypeMapping() const;

private:
    Automata *buildAutomataFromline(string line);

    bool isDefinition(string line);

    bool isExpression(string line);

    void handleDefinition(string line);

    Automata *handleExpression(string line);

    bool isTarget(string line, char desired, char other);

    bool isKeywords(string line);

    bool isPunctuation(string line);

    bool startWith(string line, char start, char end);

    Automata *handleKeywords(string line);

    Automata *handlePunctuation(string line);

    Automata *buildFromWord(string word);

    string substituteToken(string line, string source, string target);

    string substituteAll(string line);

    string handleRanges(string line);

    string buildRange(char start, char end);

    string expandRange(char start, char end);

    string infixToPostfix(string line);

    Automata *evaluateAutomata(string postFix);

    map<int, string> *typeMapping;
};


#endif //COMPILERPHASE1_AUTOMATABUILDER_H
