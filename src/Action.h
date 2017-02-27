#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include "HexBoard.h"

using namespace std;

class Action : public HexBoard {
private :
    vector<char>    movesTree;

public :
                    Action();
                    Action(char);
                    ~Action();
    void            giveUp();
    vector<char>    getMovesTree();
    char            getLatestMove();
    bool            nextMove(char, char, char);
    bool            undoMove();
};

#endif // ACTION_H
