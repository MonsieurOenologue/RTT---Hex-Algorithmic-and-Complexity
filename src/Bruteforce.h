#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "Action.h"
#include "AITools.h"
#include "AIManager.h"

class Bruteforce {
private :
    vector<ustring> movesTree;
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
