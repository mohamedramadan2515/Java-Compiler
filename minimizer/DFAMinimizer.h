//
// Created by Admin on 3/23/2017.
//

#ifndef COMPILERPHASE1_DFAMINIMIZER_H
#define COMPILERPHASE1_DFAMINIMIZER_H


#include <map>
#include <string>
#include "../automata/Node.h"
#include "PartitionSet.h"

class DFAMinimizer {

public:
    DFAMinimizer(Node *start, set<char> *allPossibleInputs) {
        this->start = start;
        this->allPossibleInputs = allPossibleInputs;
        this->pSets = new vector<PartitionSet *>();
    }

    Node *minimizeDFA();

private:
    Node *start;
    map<int, int> nodeToPartition;
    map<int, Node *> idToNode;
    map<int, PartitionSet *> idToPartition;
    vector<PartitionSet *> *pSets;
    set<char> *allPossibleInputs;

    vector<PartitionSet *> *splitPartition(PartitionSet *partition);

    void preProcess(Node *current, set<int> *vis, PartitionSet *finalStates, PartitionSet *nonFinalStates);

    string getNodeMask(Node *node);

    void adjustPartitionMapping(PartitionSet *partition);

    void connectToOtherPartitions(PartitionSet *partition);

    void adjustPartition(PartitionSet *partition);

    vector<PartitionSet *> *splitPartitionByType(PartitionSet *pSet);
};


#endif //COMPILERPHASE1_DFAMINIMIZER_H
