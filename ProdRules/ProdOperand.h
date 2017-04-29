//
// Created by Ramadan on 4/21/2017.
//

#ifndef COMPILERPHASE1_PRODOPERAND_H
#define COMPILERPHASE1_PRODOPERAND_H

#include <iostream>

using namespace std;
class ProdOperand {
public:
    ProdOperand(string name){
        this->name = name;
    }
    virtual string getName();
protected:
    string name;
};


#endif //COMPILERPHASE1_PRODOPERAND_H
