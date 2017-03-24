//
// Created by Admin on 3/23/2017.
//

#include <sstream>
#include "DFAMinimizer.h"


void DFAMinimizer::preProcess(Node *current, set<int> *vis, PartitionSet *finalStates, PartitionSet *nonFinalStates) {
    vis->insert(current->getUid());
    idToNode[current->getUid()] = current;
    if (current->isIsAccepted()) {
        nodeToPartition[current->getUid()] = finalStates->getUid();
        finalStates->insertNewNodeId(current->getUid());
    } else {
        nodeToPartition[current->getUid()] = nonFinalStates->getUid();
        nonFinalStates->insertNewNodeId(current->getUid());
    }
    for (auto p: *current->getNext()) {
        vector<Node *> v = p.second;
        for (Node *n : v) {
            if (vis->find(n->getUid()) == vis->end()) {
                preProcess(n, vis, finalStates, nonFinalStates);
            }
        }
    }
}

vector<PartitionSet *> *DFAMinimizer::splitPartition(PartitionSet *partition) {
    map<string, PartitionSet *> *partitionMapping = new map<string, PartitionSet *>();
    for (int nodeId: *partition->getNodesIds()) {
        string mask = getNodeMask(idToNode[nodeId]);
        if (partitionMapping->find(mask) == partitionMapping->end()) {
            (*partitionMapping)[mask] = new PartitionSet();
        }
        (*partitionMapping)[mask]->insertNewNodeId(nodeId);
    }
    vector<PartitionSet *> *partitions = new vector<PartitionSet *>();
    for (auto p : *partitionMapping) {
        partitions->push_back(p.second);
    }
    return partitions;
}

string DFAMinimizer::getNodeMask(Node *node) {
    string res = "";
    for (char c : *allPossibleInputs) {
        vector<Node *> *nxt = node->getNext(c);
        if (nxt->empty()) {
            res += "-";
        } else {
            int id = (*nxt)[0]->getUid();
            stringstream ss;
            ss << nodeToPartition[id];
            res += ss.str();
        }
    }
    return res;
}

void DFAMinimizer::adjustPartitionMapping(PartitionSet *partition) {
    set<int> *partitionSetIds = partition->getNodesIds();
    for (int i : *partitionSetIds) {
        nodeToPartition[i] = partition->getUid();
    }
}

Node *DFAMinimizer::minimizeDFA() {
    set<int> vis;
    PartitionSet *finalStates = new PartitionSet();
    PartitionSet *nonFinalStates = new PartitionSet();
    preProcess(start, &vis, finalStates, nonFinalStates);
    pSets->push_back(nonFinalStates);
    vector<PartitionSet *> *partitionsSpliByType = splitPartitionByType(finalStates);
    pSets->insert(pSets->end(), partitionsSpliByType->begin(), partitionsSpliByType->end());
    for(PartitionSet * p : *pSets){
        adjustPartitionMapping(p);
    }
    bool finished = false;
    while (!finished) {
        vector<PartitionSet *> *newPSets = new vector<PartitionSet *>();
        finished = true;
        for (PartitionSet *partition : *pSets) {
            vector<PartitionSet *> *tmp = splitPartition(partition);
            newPSets->insert(newPSets->end(), tmp->begin(), tmp->end());
            finished = (tmp->size() == 1) && finished;
        }
        pSets = newPSets;
        for (PartitionSet *partition: *pSets) {
            adjustPartitionMapping(partition);
        }
    }
    for (auto p : *pSets) {
        idToPartition[p->getUid()] = p;
    }
    for (auto p : *pSets) {
        connectToOtherPartitions(p);
        adjustPartition(p);
    }
    int partitionId = nodeToPartition[start->getUid()];
    return idToPartition[partitionId]->getNode();
}

void DFAMinimizer::connectToOtherPartitions(PartitionSet *partition) {
    int nodeId = *(partition->getNodesIds()->begin());
    Node *node = idToNode[nodeId];
    for (char c : *allPossibleInputs) {
        vector<Node *> *nxt = node->getNext(c);
        if (!nxt->empty()) {
            int id = (*nxt)[0]->getUid();
            int partitionId = nodeToPartition[id];
            PartitionSet *p = idToPartition[partitionId];
            partition->connect(p, c);
        }
    }
}

void DFAMinimizer::adjustPartition(PartitionSet *partition) {
    int type = INT_MAX;
    bool acceptance = false;
    for (int i : *partition->getNodesIds()) {
        Node *n = idToNode[i];
        acceptance = acceptance || n->isIsAccepted();
        type = min(type, n->getType());
    }
    partition->setType(type);
    partition->getNode()->setAccepted(acceptance);
}

vector<PartitionSet *> *DFAMinimizer::splitPartitionByType(PartitionSet *p) {
    map<int, PartitionSet *> *groupByType = new map<int, PartitionSet*>();
    for (int id : *p->getNodesIds()) {
        Node *node = idToNode[id];
        if (groupByType->find(node->getType()) == groupByType->end()) {
            (*groupByType)[node->getType()] = new PartitionSet();
        }
        (*groupByType)[node->getType()]->insertNewNodeId(id);
    }
    vector<PartitionSet *> *res = new vector<PartitionSet *>();
    for (auto pp : *groupByType) {
        res->push_back(pp.second);
    }
    return res;
}
