//
// Created by Admin on 3/22/2017.
//

#ifndef COMPILERPHASE1_DFABUILDER_H
#define COMPILERPHASE1_DFABUILDER_H


#include <stack>
#include <map>
#include "../automata/Automata.h"
#include "State.h"

class DFABuilder {
public:
    DFABuilder(Automata *nfa, set<char> *allPossibleInputs) {
        this->nfa = nfa;
        this->allPossibleInputs = allPossibleInputs;
    }

    Node *buildDFA();

private:
    Automata *nfa;
    stack<State *> unResolved;
    set<char> *allPossibleInputs;
    map<int, set<int> *> epsClojures;
    vector<State *> taken;
    map<int, Node *> idToNode;

    void preProcess(Node *current, set<int> *visited);

    void getEpsillonClojure(Node *current, set<int> *result);

    State *getNextState(char c, State *state);

    set<int> *getNodeIds(char c, Node *node);

    void adjustState(State *state);

    State *handleNewState(State *state);

    void generatePossibleStates(State *state);

public:
    vector<State *> *getTaken();

};


#endif //COMPILERPHASE1_DFABUILDER_H
