//
// Created by Admin on 3/22/2017.
//

#include <iostream>
#include "DFABuilder.hpp"

set<int> *DFABuilder::getNodeIds(char c, Node *node) {
    set<int> *res = new set<int>();
    vector<Node *> *nxt = node->getNext(c);
    for (Node *n : *nxt) {
        for (int x : *epsClojures[n->getUid()]) {
            res->insert(x);
        }
    }
    return res;
}


Node *DFABuilder::buildDFA() {
    set<int> vis;
    preProcess(this->nfa->start, &vis);
//    cout << "Pre Process Map" << endl;
//    for (auto k : epsClojures) {
//        cout << k.first << " -> ";
//        for (auto s : *k.second) {
//            cout << s << " ";
//        }
//        cout << endl;
//    }
//    cout << "End Map" << endl;
    State *start = new State(epsClojures[nfa->start->getUid()]);
    adjustState(start);
    handleNewState(start);
    while (!unResolved.empty()) {
        State *cur = unResolved.top();
        unResolved.pop();
        generatePossibleStates(cur);
    }
    return start->getNode();
}

void printState(State *state) {
    cout << "State UID is " << state->getUid() << endl;
    for (auto n : *state->getClojureSetIds()) {
        cout << n << " ";
    }
    cout << "State Finished" << endl;
}

State *DFABuilder::getNextState(char c, State *state) {
    set<int> *newStateIds = new set<int>();
    for (auto n: *state->getClojureSetIds()) {
        set<int> *tmp = getNodeIds(c, idToNode[n]);
        newStateIds->insert(tmp->begin(), tmp->end());
    }
    State *res = new State(newStateIds);
    adjustState(res);
    if (newStateIds->empty()) {
        res->isEps = true;
    }
    return res;
}

void DFABuilder::getEpsillonClojure(Node *current, set<int> *result) {
    result->insert(current->getUid());
    for (Node *n : *current->getEps()) {
        if (result->find(n->getUid()) == result->end()) {
            getEpsillonClojure(n, result);
        }
    }
}

void DFABuilder::preProcess(Node *current, set<int> *visited) {
    visited->insert(current->getUid());
    idToNode[current->getUid()] = current;
    set<int> *res = new set<int>();
    getEpsillonClojure(current, res);
    epsClojures[current->getUid()] = res;
    for (auto v: *current->getNext()) {
        vector<Node *> nxt = v.second;
        for (Node *n : nxt) {
            if (visited->find(n->getUid()) == visited->end()) {
                preProcess(n, visited);
            }
        }
    }
    for (Node *n : *current->getEps()) {
        if (visited->find(n->getUid()) == visited->end()) {
            preProcess(n, visited);
        }
    }
}

void DFABuilder::adjustState(State *state) {
    bool isAccepted = false;
    int type = INT_MAX;
    for (int i : *state->getClojureSetIds()) {
        Node *n = idToNode[i];
        isAccepted = n->isIsAccepted() || isAccepted;
        type = min(type, n->getType());
    }
    state->setAccepted(isAccepted);
    state->setType(type);
}

State *DFABuilder::handleNewState(State *state) {
    for (State *s : taken) {
        if (s->isEqual(state)) {
            return s;
        }
    }
    taken.push_back(state);
    unResolved.push(state);
    return state;
}

void DFABuilder::generatePossibleStates(State *state) {
    for (char c : *allPossibleInputs) {
        State *nxt = getNextState(c, state);
        nxt = handleNewState(nxt);
//        cout << c << endl;
//        printState(nxt);
        state->connect(c, nxt);
    }
}

vector<State *> *DFABuilder::getTaken() {
    return &taken;
}


