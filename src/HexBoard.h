#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

namespace std {
    typedef basic_string<unsigned char> ustring;
}

class HexBoard {
private :
    unsigned char       length;
    unsigned char       nbPawnsPlayed;
    unsigned char       maxNbPawns;
    unsigned char       path;
    string              players;
    ustring             movesTree;
    vector<ustring>     board;

    void                initBoard();

public :
                        HexBoard();
                        HexBoard(unsigned char newLength);
                        ~HexBoard();
    bool                setLength(unsigned char newLength);
    unsigned char       getLength();
    void                pushLatestMove(unsigned char newMove);
    unsigned char       getLatestMove();
    unsigned char       pullLatestMove();
    void                setNbPawnsPlayed(unsigned char newNbPawnsPlayed);
    unsigned char       getNbPawnsPlayed();
    unsigned char       getMaxNbPawns();
    unsigned char       getPlayerPawn();
    bool                isPlayer1Turn();
    bool                isPlayer2Turn();
    void                setPlayers(string playerL, string playerR);
    string              getPlayers();
    string              getPlayerL();
    string              getPlayerR();
    ustring             getMovesTree();
    FILE*               getRules();
    bool                swapRule();
    bool                continueGame();
    void                displayBoard();
    bool                setPosition(unsigned char pos);
    bool                setPosition(unsigned char x, unsigned char y);
    bool                resetLatestPosition();
    bool                pawnConnected(unsigned char x, unsigned char y);
    bool                victoryByLinksMemory(unsigned char p);
    bool                victoryByRecursion(unsigned char x, unsigned char y);
    unsigned char       victoryByRecursion(unsigned char x, unsigned char y, unsigned char p);
};

#endif // HEXBOARD_H
