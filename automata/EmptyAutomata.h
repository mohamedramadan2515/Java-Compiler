//
// Created by Admin on 3/21/2017.
//

#ifndef COMPILERPHASE1_EMPTYAUTOMATA_H
#define COMPILERPHASE1_EMPTYAUTOMATA_H


#include <limits.h>
#include "Automata.h"

class EmptyAutomata : public Automata {
public:
    EmptyAutomata() : Automata(INT_MAX) {}

    Automata *merge(Automata &other);

    Automata *concat(Automata &other);

    Automata *many();

    Automata *manyOne();
};


#endif //COMPILERPHASE1_EMPTYAUTOMATA_H
