//
// Created by Admin on 3/21/2017.
//

#include <iostream>
#include <climits>
#include "Automata.h"
#include "EmptyAutomata.h"

Automata *Automata::merge(Automata &other) {//OR
    Automata *x = &other;
    if (EmptyAutomata *v = dynamic_cast<EmptyAutomata *> (x)) {
        cout << "cast succeded other is empty" << endl;
        return this;
    }
    Node *newStart = new Node(false, INT_MAX);
    Node *newEnd = new Node(true, INT_MAX);
    newStart->addEpsillon(start);
    newStart->addEpsillon(other.start);
    end->addEpsillon(newEnd);
    other.end->addEpsillon(newEnd);
    this->end->setAccepted(false);
    other.end->setAccepted(false);
    return new Automata(newStart, newEnd);
}

Automata *Automata::manyOne() {//+
    this->end->addEpsillon(this->start);
    return this;
}

Automata *Automata::concat(Automata &other) {//and
    Automata *x = &other;
    if (EmptyAutomata *v = dynamic_cast<EmptyAutomata *> (x)) {
        cout << "cast succeded other is empty" << endl;
        return this;
    }
    this->end->addEpsillon(other.start);
    this->end->setAccepted(false);
    return new Automata(this->start, other.end);
}

Automata *Automata::many() {//*
    Node *newStart = new Node(false, INT_MAX);
    Node *newEnd = new Node(true, this->end->getType());
    newStart->addEpsillon(this->start);
    newStart->addEpsillon(newEnd);
    this->end->addEpsillon(this->start);
    this->end->addEpsillon(newEnd);
    this->end->setAccepted(false);
    return new Automata(newStart, newEnd);
}
