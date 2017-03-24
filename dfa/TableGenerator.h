//
// Created by Admin on 3/22/2017.
//

#ifndef COMPILERPHASE1_TABLEGENERATOR_H
#define COMPILERPHASE1_TABLEGENERATOR_H

#include <ostream>
#include "State.h"

using namespace std;

class TableGenerator {

private:
    vector<State *> *taken;
    set<char> *allPossibleInputs;

    Node *start;

    void printTableWithNode(ostream &out, set<int> *vis, Node *current);

    void printNode(Node *node, ostream &out);

public:

    TableGenerator(vector<State *> *taken, set<char> *allPossibleInputs) {
        this->taken = taken;
        this->allPossibleInputs = allPossibleInputs;
    }

    TableGenerator(Node *start, set<char> *allPossibleInputs) {
        this->start = start;
        this->allPossibleInputs = allPossibleInputs;
    }

    void printTable(ostream &out);

    void printMinimizedTable(ostream &out);

};


#endif //COMPILERPHASE1_TABLEGENERATOR_H
