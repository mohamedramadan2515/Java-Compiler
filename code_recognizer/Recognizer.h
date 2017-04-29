//
// Created by Admin on 3/24/2017.
//

#ifndef COMPILERPHASE1_RECOGNIZER_H
#define COMPILERPHASE1_RECOGNIZER_H


#include <string>
#include <map>
#include <ostream>
#include <istream>
#include "../automata/Node.h"

class Recognizer {
public:
    Recognizer(Node *start, map<int, string> *typeMapping, istream &in) : in(in) {
        this->typeMapping = typeMapping;
        this->start = start;
    }

    void recognize(ostream &out);

    vector<pair<string, string>> symbolTable;
private:
    map<int, string> *typeMapping;
    Node *start;
    istream &in;

    string recognizeToken(string token);

    void reset(int &lastAcceptedIdx, int &lastAcceptedType, int &lastStart, int &currentIdx, Node *&current) const;
};


#endif //COMPILERPHASE1_RECOGNIZER_H
