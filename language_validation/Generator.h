//
// Created by Ramadan on 4/24/2017.
//

#ifndef COMPILERPHASE1_GENERATOR_H
#define COMPILERPHASE1_GENERATOR_H

#include <bits/stdc++.h>

using namespace std;
class Generator {
public:
    Generator(string tokensFilePath){
        this->tokensFilePath = tokensFilePath;
    }
    void generate();

private:
    string tokensFilePath;
};


#endif //COMPILERPHASE1_GENERATOR_H
