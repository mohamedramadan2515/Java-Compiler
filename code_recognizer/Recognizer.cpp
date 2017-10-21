//
// Created by Admin on 3/24/2017.
//

#include <sstream>
#include "Recognizer.hpp"
#include "../utils/Constants.hpp"

void Recognizer::recognize(ostream &out) {
    string token;

    while (in >> token) {
        string tmp = recognizeToken(token);
        out << tmp;
    }
}

string Recognizer::recognizeToken(string token) {
    stringstream out;
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
                if(lastAcceptedType == Constants::PUNC){
                    symbolTable.push_back({sub, "Punc"});
                }else{
                    symbolTable.push_back({sub, "Keyword"});
                }
                reset(lastAcceptedIdx, lastAcceptedType, lastStart, currentIdx, current);
            } else {
                string sub = token.substr(lastStart, lastAcceptedIdx - lastStart + 1);
                string type = (*typeMapping)[lastAcceptedType];
                out << type << " " << endl;
                symbolTable.push_back({sub, type});
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
        if(lastAcceptedType == Constants::PUNC){
            symbolTable.push_back({sub, "Punc"});
        }else{
            symbolTable.push_back({sub, "Keyword"});
        }
        reset(lastAcceptedIdx, lastAcceptedType, lastStart, currentIdx, current);
    } else {
        string sub = token.substr(lastStart, lastAcceptedIdx - lastStart + 1);
        string type = (*typeMapping)[lastAcceptedType];
        out << type << " " << endl;
        symbolTable.push_back({sub, type});
        reset(lastAcceptedIdx, lastAcceptedType, lastStart, currentIdx, current);
    }
    return out.str();
}

void
Recognizer::reset(int &lastAcceptedIdx, int &lastAcceptedType, int &lastStart, int &currentIdx, Node *&current) const {
    lastStart = lastAcceptedIdx + 1;
    currentIdx = lastAcceptedIdx + 1;
    current = start;
    lastAcceptedType = lastAcceptedIdx = -1;
}

