//
// Created by Admin on 3/21/2017.
//

#ifndef COMPILERPHASE1_AUTOMATA_H
#define COMPILERPHASE1_AUTOMATA_H

#include <iostream>
#include <climits>
#include "Node.hpp"

using namespace std;

class Automata {
public:
  Node *start;
  Node *end;

  Automata(const int type);
  Automata(const char c, const int type);
  Automata(Node *start, Node *end);

  virtual bool isEmptyAutomata();

  // Merge the current Automata with
  // the given one.
  virtual Automata* merge(Automata &other);

  // And the given Automata with
  // the given one.
  virtual Automata* concat(Automata &other);

  // Create an Automata that will try
  // to run the current automata zero or more times.
  virtual Automata* many();

  // Create an Automata that will try
  // to run the current automata on or more times.
  virtual Automata* manyOne();
};


#endif //COMPILERPHASE1_AUTOMATA_H
