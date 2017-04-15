#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <cstdlib>
#include <time.h>
#include "Action.h"
#include "AITools.h"
#include "AIManager.h"

class Bruteforce {
private :
    vector<ustring> player1;
    vector<ustring> player2;
    bool            generated;
    bool            random;

public :
                    Bruteforce();
                    ~Bruteforce();
    void            generateRecursiveMovesTree(unsigned char length, bool randomize);
    void            generateRecursiveMovesTree(Action boardTemp, ustring pos);
    void            sortPlayer1(unsigned char maxBranchLength);
    void            sortPlayer2(unsigned char maxBranchLength);
    bool            playNextMove(Action &currentBoardState);
    void            displayPlayer1MovesTree();
    void            displayPlayer2MovesTree();
};

#endif // BRUTEFORCE_H
