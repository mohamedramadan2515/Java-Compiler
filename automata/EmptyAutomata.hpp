//
// Created by Admin on 3/21/2017.
//

#ifndef COMPILERPHASE1_EMPTYAUTOMATA_H
#define COMPILERPHASE1_EMPTYAUTOMATA_H

#include <assert.h>
#include <limits.h>
#include "Automata.hpp"

class EmptyAutomata : public Automata {
public:
  EmptyAutomata() : Automata(INT_MAX) {}

  bool isEmptyAutomata() override;

  Automata* merge(Automata& other) override;

  Automata* concat(Automata& other) override;

  Automata* many() override;

  Automata* manyOne() override;
};

#endif //COMPILERPHASE1_EMPTYAUTOMATA_H
