//
// Created by Admin on 3/23/2017.
//

#include "PartitionSet.h"

void PartitionSet::insertNewNodeId(int id) {
    nodesIds->insert(id);
}

int PartitionSet::nextId = 0;

int PartitionSet::getUid() const {
    return uid;
}

set<int> *PartitionSet::getNodesIds() const {
    return nodesIds;
}

Node *PartitionSet::getNode() const {
    return node;
}

void PartitionSet::connect(PartitionSet *partition, char c) {
    this->node->addNext(c, partition->getNode());
}

void PartitionSet::setType(int type) {
    node->setType(type);
}


