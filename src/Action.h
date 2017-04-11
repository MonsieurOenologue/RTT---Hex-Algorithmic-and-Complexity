#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include "HexBoard.h"

using namespace std;

class Action : public HexBoard {
private :
    string          movesTree;

public :
                    Action();
                    Action(unsigned char);
                    ~Action();
    void            giveUp();
    string          getMovesTree();
    unsigned char   pullLatestMove();
    bool            nextMove(unsigned char);
    bool            undoMove();
};

#endif // ACTION_H
