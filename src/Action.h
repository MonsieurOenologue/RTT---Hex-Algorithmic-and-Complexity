#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class Action {
private :


public :
            Action();
            ~Action();
    void    giveUp();
    vector<int>   getMoveTree();
    int     latestMove();
    bool    nextMove();
    bool    undoMove();
};

#endif // ACION_H
