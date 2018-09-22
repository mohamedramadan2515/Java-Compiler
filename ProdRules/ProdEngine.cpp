//
// Created by Ramadan on 4/22/2017.
//

#include "ProdEngine.h"

map<pair<NonTerminal *, Terminal *>, Expression *> *ProdEngine::getTable() {
    return table;
}

NonTerminal *ProdEngine::getStart() {
    return  start;
}

map<string, Terminal *> ProdEngine::getTerminalsMap() {
    return terminalsMap;
}
