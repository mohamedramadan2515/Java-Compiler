//
// Created by Ramadan on 4/21/2017.
//

#ifndef COMPILERPHASE1_TERMINAL_H
#define COMPILERPHASE1_TERMINAL_H

#include "ProdOperand.hpp"
#include <vector>

using namespace std;
class Terminal : public ProdOperand{
public:
    Terminal(string name) : ProdOperand(name){
    }

};


#endif //COMPILERPHASE1_TERMINAL_H
