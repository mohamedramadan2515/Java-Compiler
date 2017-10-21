//
// Created by Admin on 3/21/2017.
//

#include "EmptyAutomata.hpp"

bool EmptyAutomata::isEmptyAutomata() {
  return true;
}

Automata* EmptyAutomata::merge(Automata &other) {
    return &other;
}

Automata* EmptyAutomata::concat(Automata &other) {
    return &other;
}

Automata* EmptyAutomata::many() {
    assert(false);
}

Automata* EmptyAutomata::manyOne() {
    assert(false);
}
