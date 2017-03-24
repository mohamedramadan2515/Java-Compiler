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
    Recognizer(Node *start, map<int, string> *typeMapping) {
        this->typeMapping = typeMapping;
        this->start = start;
    }

    void recognize(ostream &out, istream &in);

private:
    map<int, string> *typeMapping;
    Node *start;;


    void recognizeToken(string token, ostream &out);

    void reset(int &lastAcceptedIdx, int &lastAcceptedType, int &lastStart, int &currentIdx, Node *&current) const;
};


#endif //COMPILERPHASE1_RECOGNIZER_H
