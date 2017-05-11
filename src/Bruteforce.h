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
    void            generateMovesTree(unsigned char length, bool randomize);
    vector<ustring> generateOptimizedFirstMove(Action boardTemp, ustring pos);
    unsigned char   generateMovesTree(Action boardTemp, ustring pos, vector<ustring> &solvedP1, vector<ustring> &solvedP2);
    bool            playNextMove(Action &currentBoardState);
    void            displayPlayer1MovesTree();
    void            displayPlayer2MovesTree();
};

#endif // BRUTEFORCE_H
