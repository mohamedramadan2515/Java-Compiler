//
// Created by Admin on 3/22/2017.
//

#include "State.hpp"

int State::getUid() {
    return node->getUid();
}

set<int> *State::getClojureSetIds() {
    return &clojureSetIds;
}

Node *State::getNode() {
    return node;
}

void State::connect(char c, State *other) {
    if (other->isEps)return;
    this->node->addNext(c, other->getNode());
}

void State::setType(int type) {
    node->setType(type);
}
