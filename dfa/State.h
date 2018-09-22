//
// Created by Admin on 3/22/2017.
//

#ifndef COMPILERPHASE1_STATE_H
#define COMPILERPHASE1_STATE_H

#include <set>
#include <limits.h>
#include "../automata/Node.h"

using namespace std;

class State {
private:
    set<int> clojureSetIds;
    Node *node;


public:

    State(set<int> *clojureSetIds) {
        node = new Node(false, INT_MAX);
        this->clojureSetIds = *clojureSetIds;
    }

    State(bool isAccepted) {
        node = new Node(isAccepted, INT_MAX);
    }

    void setAccepted(bool accepted) {
        node->setAccepted(accepted);
    }


    bool isEps = false;

    int getUid();

    set<int> *getClojureSetIds();


    Node *getNode();

    bool isEqual(State *other) {
        return *(other->getClojureSetIds()) == (this->clojureSetIds);
    }

    void addId(int id) {
        clojureSetIds.insert(id);
    }

    void setType(int type);

    void connect(char c, State *other);

};


#endif //COMPILERPHASE1_STATE_H
