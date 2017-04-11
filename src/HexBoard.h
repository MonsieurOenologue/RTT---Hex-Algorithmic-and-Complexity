#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <time.h>

using namespace std;

class HexBoard {
private :
    unsigned char   length;
    unsigned char   nbPawnsPlayed;
    unsigned char   latestMove;
    unsigned char   path;
    string          players;
    vector<string>  board;
    vector<string>  leftToRightSide;
    vector<string>  rightToLeftSide;
    vector<string>  highToLowSide;
    vector<string>  lowToHighSide;

    void    initBoard();

public :
                    HexBoard();
                    HexBoard(unsigned char newLength);
                    ~HexBoard();
    bool            setLength(unsigned char newLength);
    unsigned char   getLength();
    void            setLatestMove(unsigned char previousLatestMove);
    unsigned char   getLatestMove();
    void            setNbPawnsPlayed(unsigned char newNbPawnsPlayed);
    unsigned char   getNbPawnsPlayed();
    void            setPlayers(string playerL, string playerR);
    string          getPlayers();
    string          getPlayerL();
    string          getPlayerR();
    FILE*           getRules();
    bool            swapRule();
    bool            continueGame();
    void            displayBoard();
    bool            setPosition(unsigned char x, unsigned char y, unsigned char v);
    bool            pawnConnected(unsigned char x, unsigned char y);
    bool            victoryByLinksMemory(unsigned char p);
    bool            victoryByRecursion(unsigned char x, unsigned char y);
    unsigned char   victoryByRecursion(unsigned char x, unsigned char y, unsigned char p);

};

#endif // HEXBOARD_H
