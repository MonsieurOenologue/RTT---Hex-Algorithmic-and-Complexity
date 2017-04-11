#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include "Action.h"
#include "HexBoard.h"
#include "AITools.h"
#include "AIManager.h"

using namespace std;

class Bruteforce {
private :
    vector<string>  movesTree;
    bool            random;
    bool            first;

public :
                    Bruteforce();
                    ~Bruteforce();
    bool            getFirst();
    bool            playNextMove(Action &currentBoardState);
    void            generateMovesTree(unsigned char length, bool player1, bool randomize);
    void            displayMovesTree();
};

#endif // BRUTEFORCE_H
