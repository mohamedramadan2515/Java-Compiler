//
// Created by Admin on 3/21/2017.
//
#include "Automata.hpp"

Automata::Automata(const int type) {
  start = new Node(false, INT_MAX);
  end = new Node(true, type);
  start->addEpsillon(end);
}

Automata::Automata(const char c, const int type) {
  start = new Node(false, INT_MAX);
  end = new Node(true, type);
  start->addNext(c, end);
}

Automata::Automata(Node *start, Node *end) {
  this->start = start;
  this->end = end;
}

bool Automata::isEmptyAutomata() {
  return false;
}

Automata* Automata::merge(Automata &other) {//OR
  if (other.isEmptyAutomata()) {
    return this;
  }
  Node* newStart = new Node(false, INT_MAX);
  Node* newEnd = new Node(true, INT_MAX);
  newStart->addEpsillon(start);
  newStart->addEpsillon(other.start);
  end->addEpsillon(newEnd);
  other.end->addEpsillon(newEnd);
  this->end->setAccepted(false);
  other.end->setAccepted(false);
  return new Automata(newStart, newEnd);
}

Automata* Automata::manyOne() {//+
  this->end->addEpsillon(this->start);
  return this;
}

Automata* Automata::concat(Automata &other) {//and
  if (other.isEmptyAutomata()) {
    return this;
  }
  this->end->addEpsillon(other.start);
  this->end->setAccepted(false);
  return new Automata(this->start, other.end);
}

Automata* Automata::many() {//*
  Node *newStart = new Node(false, INT_MAX);
  Node *newEnd = new Node(true, this->end->getType());
  newStart->addEpsillon(this->start);
  newStart->addEpsillon(newEnd);
  this->end->addEpsillon(this->start);
  this->end->addEpsillon(newEnd);
  this->end->setAccepted(false);
  return new Automata(newStart, newEnd);
}
