//
// Created by Admin on 3/21/2017.
//

#ifndef COMPILERPHASE1_AUTOMATA_H
#define COMPILERPHASE1_AUTOMATA_H

#include <climits>
#include "Node.h"

using namespace std;

class Automata {
public:
    Automata(int type) {
        start = new Node(false, INT_MAX);
        end = new Node(true, type);
        start->addEpsillon(end);
    }

    Automata(char c, int type) {
        start = new Node(false, INT_MAX);
        end = new Node(true, type);
        start->addNext(c, end);
    }

    Automata(Node *start, Node *end) {
        this->start = start;
        this->end = end;
    }

    Node *start;
    Node *end;

    virtual Automata *merge(Automata &other);

    virtual Automata *concat(Automata &other);

    virtual Automata *many();

    virtual Automata *manyOne();

};


#endif //COMPILERPHASE1_AUTOMATA_H
