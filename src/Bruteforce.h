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
    bool            random;
    bool            first;

public :
                    Bruteforce();
                    ~Bruteforce();
    bool            getFirst();
    bool            playNextMove(Action &currentBoardState);
    void            generateRecursiveMovesTree(unsigned char length, bool playFirst, bool randomize);
    void            generateRecursiveMovesTree(Action boardTemp, ustring pos);
    void            sortPlayer1(unsigned char maxNbPawns);
    void            displayPlayer1MovesTree();
    void            displayPlayer2MovesTree();
};

#endif // BRUTEFORCE_H
