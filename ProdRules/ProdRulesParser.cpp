//
// Created by Ramadan on 4/21/2017.
//

#include "ProdRulesParser.h"
#include "../utils/string_utils.h"
#include "Expression.h"
#include <bits/stdc++.h>

void ProdRulesParser::parse() {
    ifstream myfile;
    myfile.open(filePath);
    while (!myfile.eof()) {
        string line;
        getline(myfile, line);
        handleInputLine(line);
    }
}

void ProdRulesParser::handleInputLine(string line) {
    if (isNewProd(line)) {
        NonTerminal *LHS = handleLHS(line);
        if(lastNonTerminal == NULL){
            start = LHS;
        }
        lastNonTerminal = LHS;
        handleRHS(line, LHS);
    } else {
        if (lastNonTerminal == NULL)
            assert(false);
        addExpressions(line, lastNonTerminal);
    }
}

NonTerminal *ProdRulesParser::handleLHS(string &line) {
    string nonTerminalName = "";
    int idx = 0;
    while (idx < line.size() && (line[idx] == ' ' || line[idx] == '#'))idx++;
    while (idx < line.size() && line[idx] != '=' && line[idx] != ' ') {
        nonTerminalName += line[idx++];
    }
    NonTerminal *LHS;
    if (nonTerminalsMap.find(nonTerminalName) != nonTerminalsMap.end()) {
        LHS = nonTerminalsMap[nonTerminalName];
    } else {
        LHS = new NonTerminal(nonTerminalName);
        nonTerminalsMap[nonTerminalName] = LHS;
    }
    return LHS;
}

vector<Terminal *> *ProdRulesParser::getTerminals() {
    terminals.clear();
    for (auto it : terminalsMap) {
        terminals.push_back(it.second);
    }
    return &terminals;
}

vector<NonTerminal *> *ProdRulesParser::getNonTerminals() {
    nonTerminals.clear();
    for (auto it : nonTerminalsMap) {
        nonTerminals.push_back(it.second);
    }
    return &nonTerminals;
}

bool ProdRulesParser::isNewProd(string line) {
    int idx = 0;
    while (idx < line.size() && line[idx] == ' ')idx++;
    if (idx == line.size())return false;
    return line[idx] == '#';
}

void ProdRulesParser::handleRHS(string line, NonTerminal *LHS) {
    int idx = 0;
    while (idx < line.size() && line[idx] != '=')idx++;
    if (idx == line.size()) {
        assert(false);
    }
    string exp = "";
    for (int i = idx + 1; i < line.size(); i++)
        exp += line[i];
    addExpressions(exp, LHS);
}

void ProdRulesParser::addExpressions(string expStr, NonTerminal *LHS) {
    vector<string> *expStrings = splitOver(expStr, '|');
    for (string exp : *expStrings) {
        convertStrtoExp(exp, LHS);
    }
}

void ProdRulesParser::convertStrtoExp(string expString, NonTerminal *LHS) {
    int idx = 0;
    Expression *exp = new Expression();
    while (idx < expString.size()) {
        while (idx < expString.size() && expString[idx] == ' ')idx++;
        if (idx < expString.size() && expString[idx] == '\'') { // terminal
            idx = handleTerminal(expString, idx, exp);
        } else if(idx < expString.size()){
            idx = handleNonTerminal(expString, idx, exp);
        }
    }
    LHS->addExp(exp);
    exp->addLHS(LHS);
}

int ProdRulesParser::handleNonTerminal(string &expString, int idx, Expression *exp) {
    string nonTerminalName = "";
    while (idx < expString.size() && expString[idx] != '\'' && expString[idx] != ' ') {
        nonTerminalName += expString[idx++];
    }
    NonTerminal *nonTerminal;
    if (nonTerminalsMap.find(nonTerminalName) != nonTerminalsMap.end()) {
        nonTerminal = nonTerminalsMap[nonTerminalName];
    } else {
        nonTerminal = new NonTerminal(nonTerminalName);
        nonTerminalsMap[nonTerminalName] = nonTerminal;
    }
    exp->addOperand(nonTerminal);
    nonTerminal->addAssociatedExp(exp);
    return idx;
}

int ProdRulesParser::handleTerminal(string &expString, int idx, Expression *exp) {
    string terminalName = "";
    idx++;
    while (idx < expString.size() && expString[idx] != '\'') {
        terminalName += expString[idx++];
    }
    idx++;
    Terminal *terminal;
    if (terminalsMap.find(terminalName) != terminalsMap.end()) {
        terminal = terminalsMap[terminalName];
    } else {
        terminal = new Terminal(terminalName);
        terminalsMap[terminalName] = terminal;
    }
    exp->addOperand(terminal);
    return idx;
}

Terminal* ProdRulesParser::epsilon = new Terminal("\\L");
Terminal* ProdRulesParser::endOfExp = new Terminal("$");

NonTerminal *ProdRulesParser::getStart() {
    return start;
}

map<string, Terminal *> ProdRulesParser::getTerminalsMap() {
    return terminalsMap;
}
