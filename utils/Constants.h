//
// Created by Admin on 3/23/2017.
//

#ifndef COMPILERPHASE1_CONSTANTS_H
#define COMPILERPHASE1_CONSTANTS_H


class Constants {
    static int nextId;

public:

    const static int KEY_WORD = -3;
    const static int PUNC = -2;

    static int getType() {
        return nextId++;
    }
};


#endif //COMPILERPHASE1_CONSTANTS_H
