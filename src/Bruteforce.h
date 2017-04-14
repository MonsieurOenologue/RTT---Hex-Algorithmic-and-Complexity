#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <cstdlib>
#include <time.h>
#include "Action.h"
#include "AITools.h"
#include "AIManager.h"

class Bruteforce {
private :
    vector<ustring> movesTree;
    vector<ustring> badMoves;
    bool            random;
    bool            first;

public :
                    Bruteforce();
                    ~Bruteforce();
    bool            getFirst();
    bool            playNextMove(Action &currentBoardState);
    void            generateMovesTree(unsigned char length, bool player1, bool randomize);
    void            generateRecursiveMovesTree(unsigned char length, bool player1, bool randomize);
    bool            generateRecursiveMovesTree(Action boardTemp, ustring pos);
    void            displayMovesTree();
};

#endif // BRUTEFORCE_H
