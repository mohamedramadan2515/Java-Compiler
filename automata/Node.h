//
// Created by Admin on 3/21/2017.
//

#ifndef COMPILERPHASE1_NODE_H
#define COMPILERPHASE1_NODE_H

#include <unordered_map>
#include <vector>

using namespace std;

class Node {
private:
    bool isAccepted;
    unordered_map<char, vector<Node *>> next;
    vector<Node *> eps;
    int uid;
    int type;
    static int nextId;
public:
    Node(bool isAccepted, int type) {
        this->isAccepted = isAccepted;
        this->uid = Node::getUniqueId();
        this->type = type;
    }

    static int getUniqueId() {
        return nextId++;
    }


    int getType() const;

    void setType(int type);

    unordered_map<char, vector<Node *>> *getNext();

    void addEpsillon(Node *node);

    void addNext(char c, Node *node);

    vector<Node *> *getNext(char c);

    int getUid() const;

    void setAccepted(bool accepted);

    bool isIsAccepted() const;

    vector<Node *> *getEps();
};


#endif //COMPILERPHASE1_NODE_H
