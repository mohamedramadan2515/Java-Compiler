//
// Created by Admin on 3/21/2017.
//

#include <fstream>
#include <iostream>
#include <ctype.h>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <stack>
#include "AutomataBuilder.h"
#include "../utils/string_utils.h"
#include "../automata/EmptyAutomata.h"
#include "../utils/Constants.h"

Automata *AutomataBuilder::build(string filePath) {
    Automata *init = new EmptyAutomata();
    ifstream myfile;
    myfile.open(filePath);
    while (!myfile.eof()) {
        string line;
        getline(myfile, line);
        line = trim(line);
        init = init->merge(*buildAutomataFromline(line));
    }
    return init;
}

Automata *AutomataBuilder::buildAutomataFromline(string line) {
    Automata *res = new EmptyAutomata();
    if (isDefinition(line)) {
        handleDefinition(line);
    } else if (isExpression(line)) {
        res = res->merge(*handleExpression(line));
    } else if (isKeywords(line)) {
        res = res->merge(*handleKeywords(line));
    } else if (isPunctuation(line)) {
        res = res->merge(*handlePunctuation(line));
    } else {
        cout << "WARNING: unhandled input ^_|_^\n";
    }
    return res;
}

bool AutomataBuilder::isDefinition(string line) {
    return isTarget(line, '=', ':');
}

bool AutomataBuilder::isTarget(string line, char desired, char other) {
    for (char c : line) {
        if (c == desired) {
            return true;
        }
        if (c == other) {
            return false;
        }
    }
    return false;
}

bool AutomataBuilder::isExpression(string line) {
    return isTarget(line, ':', '=');
}

void AutomataBuilder::handleDefinition(string line) {
    line = substituteToken(line, " ", "");
    unsigned int idx = line.find('=');
    string operand = line.substr(0, idx);
    operand = trim(operand);
    string val = line.substr(idx + 1);
    val = trim(val);
    val = handleRanges(val);
    definitions[operand] = substituteAll(val);
    definitionsIds.push_back(operand);
}

string AutomataBuilder::handleRanges(string line) {
    vector<pair<string, string>> subs;
    vector<int> indx;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '\\') {
            i++;
        } else if (line[i] == '-') {
            if (i == 0 || i == line.size() - 1) {
//                assert(false);
                indx.push_back(i);
                continue;
            }
            char before = line[i - 1];
            char after = line[i + 1];
            string range = expandRange(before, after);
            if (range == "") {
                indx.push_back(i);
                continue;
            }
            string key = "";
            subs.push_back({key + before + "-" + after, range});
        }
    }
    for (int i = 0; i < indx.size(); i++) {
        line = line.insert(indx[i] + i, "\\");
//        line = line.substr(0, indx[i]) + "\\" + line.substr(indx[i]);
    }
    for (pair<string, string> p : subs) {
        line = substituteToken(line, p.first, p.second);
    }
    return line;
}

string AutomataBuilder::expandRange(char start, char end) {
    if (start > end) {
        cout << "incorrect range start > end";
//        assert(false);
        return "";
    }
    if (start >= 'a' && start <= 'z' && end >= 'a' && end <= 'z') {
        return buildRange(start, end);
    } else if (start >= 'A' && start <= 'Z' && end >= 'A' && end <= 'Z') {
        return buildRange(start, end);
    } else if (start >= '0' && start <= '9' && end >= '0' && end <= '9') {
        return buildRange(start, end);
    } else {
        cout << "expand range failed\n";
        return "";
    }
}

string AutomataBuilder::buildRange(char start, char end) {
    string res = "(";
    for (char c = start; c <= end; c++) {
        res = res + c;
        if (c != end) {
            res = res + "|";
        }
    }
    res += ")";
    return res;
}

Automata *AutomataBuilder::handleExpression(string line) {
    line = substituteToken(line, " ", "");
    unsigned int idx = line.find(':');
    string operand = line.substr(0, idx);
    operand = trim(operand);
    string val = line.substr(idx + 1);
    val = trim(val);
    val = substituteAll(val);
    val = handleRanges(val);
    val = infixToPostfix(val);
    Automata *res = evaluateAutomata(val);
    int type = Constants::getType();
    res->end->setType(type);
    (*typeMapping)[type] = operand;
    return res;
}

bool AutomataBuilder::isKeywords(string line) {
    return startWith(line, '{', '}');
}

bool AutomataBuilder::startWith(string line, char start, char end) {
    return !line.empty() && line[0] == start && line[line.size() - 1] == end;
}

bool AutomataBuilder::isPunctuation(string line) {
    return startWith(line, '[', ']');
}

Automata *AutomataBuilder::handleKeywords(string line) {
    line[0] = ' ';
    line[line.size() - 1] = ' ';
    stringstream ss(line);
    Automata *res = new EmptyAutomata();
    while (ss >> line) {
        res = res->merge(*buildFromWord(line));
    }
    return res;
}

Automata *AutomataBuilder::handlePunctuation(string line) {
    line[0] = ' ';
    line[line.size() - 1] = ' ';
    Automata *res = new EmptyAutomata();
    for (int i = 0; i < line.size(); i++) {
        if (isspace(line[i])) continue;
        if (line[i] == '\\') {
            allPossibleInputs.insert(line[i + 1]);
            res = res->merge(*new Automata(line[++i], Constants::PUNC));
        } else {
            allPossibleInputs.insert(line[i]);
            res = res->merge(*new Automata(line[i], Constants::PUNC));
        }
    }
    return res;
}

Automata *AutomataBuilder::buildFromWord(string word) {
    Automata *res = new EmptyAutomata();
    for (int i = 0; i < word.length(); ++i) {
        allPossibleInputs.insert(word[i]);
        Automata *nxt;
        if (i == word.length() - 1) {
            nxt = new Automata(word[i], Constants::KEY_WORD);
        } else {
            nxt = new Automata(word[i], INT_MAX);
        }
        res = res->concat(*nxt);
    }
    return res;
}

string AutomataBuilder::substituteToken(string line, string source, string target) {
    std::string::size_type n = 0;
    while ((n = line.find(source, n)) != std::string::npos) {
        line.replace(n, source.size(), target);
        n += target.size();
    }
    return line;
}

string AutomataBuilder::substituteAll(string line) {
    sort(definitionsIds.rbegin(), definitionsIds.rend());
    for (auto token : definitionsIds) {
        string target = "(" + definitions[token] + ")";
        line = substituteToken(line, token, target);
    }
    return line;
}

string AutomataBuilder::infixToPostfix(string line) {
    stack<char> stk;
    string postFix = "";
    for (int i = 0; i < line.size(); i++) {
        if (operationPrecedence.find(line[i]) != operationPrecedence.end() || line[i] == '(') {
            while (line[i] != '(' && !stk.empty() && operationPrecedence[stk.top()] >= operationPrecedence[line[i]]) {
                postFix = postFix + stk.top();
                stk.pop();
            }
            stk.push(line[i]);
        } else if (line[i] == ')') {
            while (!stk.empty() && stk.top() != '(') {
                postFix = postFix + stk.top();
                stk.pop();
            }
            stk.pop();
        } else if (line[i] == '\\') {
            postFix = postFix + line[i] + line[i + 1];
        } else {
            postFix = postFix + line[i];
        }
        if (i != line.size() - 1) {
            char cur = line[i];
            char nxt = line[i + 1];
            if (cur == '\\') {
                if (i + 2 >= line.size()) {
                    i++;
                    continue;
                }
                nxt = line[i + 2];
                i++;
            }
            if ((cur == '|' || nxt == '|') || (nxt == ')') || (cur == '(') || nxt == '*' || nxt == '+') {
                continue;
            }
            while (!stk.empty() && operationPrecedence[stk.top()] >= operationPrecedence[' ']) {
                postFix = postFix + stk.top();
                stk.pop();
            }
            stk.push(' ');
        }
    }
    while (!stk.empty()) {
        postFix = postFix + stk.top();
        stk.pop();
    }
    return postFix;
}

Automata *AutomataBuilder::evaluateAutomata(string postFix) {
    stack<Automata *> stk;
    for (int i = 0; i < postFix.size(); i++) {
        if (operationPrecedence.find(postFix[i]) != operationPrecedence.end()) {
            Automata *operand1, *operand2;
            switch (postFix[i]) {
                case '+':
                    operand1 = stk.top();
                    stk.pop();
                    stk.push(operand1->manyOne());
                    break;
                case '*':
                    operand1 = stk.top();
                    stk.pop();
                    stk.push(operand1->many());
                    break;
                case '|':
                    operand1 = stk.top();
                    stk.pop();
                    operand2 = stk.top();
                    stk.pop();
                    stk.push(operand2->merge(*operand1));
                    break;
                case ' ':
                    operand1 = stk.top();
                    stk.pop();
                    operand2 = stk.top();
                    stk.pop();
                    stk.push(operand2->concat(*operand1));
            }
        } else {
            Automata *current;
            if (postFix[i] == '\\' && postFix[i + 1] != 'L') {
                allPossibleInputs.insert(postFix[i + 1]);
                current = new Automata(postFix[i + 1], INT_MAX);
                i++;
            } else if (postFix[i] == '\\') {
                current = new Automata(INT_MAX);
                i++;
            } else {
                allPossibleInputs.insert(postFix[i]);
                current = new Automata(postFix[i], INT_MAX);
            }
            stk.push(current);
        }
    }
    return stk.top();
}

set<char> *AutomataBuilder::getAllPossibleInputs() {
    return &allPossibleInputs;
}

map<int, string> *AutomataBuilder::getTypeMapping() const {
    return typeMapping;
}
