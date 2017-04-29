//
// Created by Admin on 3/22/2017.
//

#include <iostream>
#include "TableGenerator.h"

void TableGenerator::printTable(ostream &out) {
    out << "State  Type";
    for (char c : *allPossibleInputs) {
        out << c << " ";
    }
    out << "\n";
    for (State *s : *taken) {
        if (s->isEps) continue;
        out << s->getNode()->isIsAccepted() << " ";
        out << s->getUid() << " ";
        if (s->getNode()->isIsAccepted()) {
            out << s->getNode()->getType() << " ";
        } else {
            out << "- ";
        }
        for (char c : *allPossibleInputs) {
            vector<Node *> *nxtV = s->getNode()->getNext(c);
            if (nxtV->size() == 0) {
                out << "- ";
            } else {
                Node *n = (*nxtV)[0];
                out << n->getUid() << " ";
            }
        }
        out << "\n";
    }
}

void TableGenerator::printNode(Node *node, ostream &out) {
    out << node->isIsAccepted() << " ";
    out << node->getUid() << " ";
    if (node->isIsAccepted()) {
        out << node->getType() << " ";
    } else {
        out << "- ";
    }
    for (char c : *allPossibleInputs) {
        vector<Node *> *v = node->getNext(c);
        if (v->empty()) {
            out << "- ";
        } else {
            Node *s = (*v)[0];
            out << s->getUid() << " ";
        }
    }
    out << endl;
}

void TableGenerator::printTableWithNode(ostream &out, set<int> *vis, Node *current) {
    vis->insert(current->getUid());
    cnt++;
    printNode(current, out);
    for (auto p : *current->getNext()) {
        vector<Node *> nxt = p.second;
        if (nxt.empty()) {
            continue;
        }
        Node *v = nxt[0];
        if (vis->find(v->getUid()) == vis->end()) {
            printTableWithNode(out, vis, v);
        }
    }
}

void TableGenerator::printMinimizedTable(ostream &out) {
    out << "A State Type ";
    for (char c : *allPossibleInputs) {
        out << c << " ";
    }
    out << "\n";
    set<int> vis;
    printTableWithNode(out, &vis, start);

    cout << "number of states : " << cnt;
}
