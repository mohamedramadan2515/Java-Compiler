//
// Created by Admin on 3/24/2017.
//

#include "Recognizer.h"
#include "../utils/Constants.h"

void Recognizer::recognize(ostream &out, istream &in) {
    string token;
    while (in >> token) {
        recognizeToken(token, out);
    }
}

void Recognizer::recognizeToken(string token, ostream &out) {
    int lastAcceptedIdx = -1;//idx in token
    int lastAcceptedType = -1;//type of last accepted
    int lastStart = 0;
    int currentIdx = 0;
    Node *current = start;
    while (currentIdx < token.size()) {
        vector<Node *> *nxt = current->getNext(token[currentIdx]);
        if (nxt->empty()) {
            if (lastAcceptedIdx == -1) {
                string sub = token.substr(lastStart, currentIdx - lastStart + 1);
                out << sub << " Error" << endl;
                lastStart = currentIdx + 1;
                currentIdx++;
                current = start;
            } else if (lastAcceptedType == Constants::KEY_WORD || lastAcceptedType == Constants::PUNC) {
                string sub = token.substr(lastStart, lastAcceptedIdx - lastStart + 1);
                out << sub << " " << endl;
                reset(lastAcceptedIdx, lastAcceptedType, lastStart, currentIdx, current);
            } else {
                string type = (*typeMapping)[lastAcceptedType];
                out << type << " " << endl;
                reset(lastAcceptedIdx, lastAcceptedType, lastStart, currentIdx, current);
            }
        } else {
            Node *nextNode = (*nxt)[0];
            if (nextNode->isIsAccepted()) {
                lastAcceptedIdx = currentIdx;
                lastAcceptedType = nextNode->getType();
            }
            current = nextNode;
            currentIdx++;
        }
    }
    if (lastAcceptedIdx == -1) {
        string sub = token.substr(lastStart, currentIdx - lastStart + 1);
        out << sub << " Error" << endl;
        lastStart = currentIdx + 1;
        currentIdx++;
        current = start;
    } else if (lastAcceptedType == Constants::KEY_WORD || lastAcceptedType == Constants::PUNC) {
        string sub = token.substr(lastStart, lastAcceptedIdx - lastStart + 1);
        out << sub << " " << endl;
        reset(lastAcceptedIdx, lastAcceptedType, lastStart, currentIdx, current);
    } else {
        string type = (*typeMapping)[lastAcceptedType];
        out << type << " " << endl;
        reset(lastAcceptedIdx, lastAcceptedType, lastStart, currentIdx, current);
    }
}

void
Recognizer::reset(int &lastAcceptedIdx, int &lastAcceptedType, int &lastStart, int &currentIdx, Node *&current) const {
    lastStart = lastAcceptedIdx + 1;
    currentIdx = lastAcceptedIdx + 1;
    current = start;
    lastAcceptedType = lastAcceptedIdx = -1;
}

