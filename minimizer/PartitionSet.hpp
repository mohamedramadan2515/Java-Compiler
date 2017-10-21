//
// Created by Admin on 3/23/2017.
//

#ifndef COMPILERPHASE1_PARTITIONSET_H
#define COMPILERPHASE1_PARTITIONSET_H

#include <set>
#include <limits.h>
#include "../automata/Node.hpp"

using namespace std;

class PartitionSet {

public:
    PartitionSet(set<int> *nodesIds) {
        uid = getUniqueId();
        this->nodesIds = nodesIds;
        node = new Node(false, INT_MAX);
    }

    PartitionSet() {
        uid = getUniqueId();
        nodesIds = new set<int>();
        node = new Node(false, INT_MAX);
    }

    void insertNewNodeId(int id);

    set<int> *getNodesIds() const;

    int getUid() const;

    Node *getNode() const;

    void setType(int type);

    void connect(PartitionSet *partition, char c);

private:
    Node *node;
    set<int> *nodesIds;
    int uid;
    static int nextId;

    static int getUniqueId() {
        return nextId++;
    }
};


#endif //COMPILERPHASE1_PARTITIONSET_H
