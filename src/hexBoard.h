#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <math.h>

using namespace std;

class HexBoard {
private :
    char            length;
    char            nbPawnsPlayed;
    string          players;
    vector<string>  board;
    vector<string>  leftToRightSide;
    vector<string>  rightToLeftSide;
    vector<string>  highToLowSide;
    vector<string>  lowToHighSide;

public :
            HexBoard();
            HexBoard(char newLength);
            ~HexBoard();
    void    setLength(char newLength);
    char    getLength();
    void    setNbPawnsPlayed(char newNbPawnsPlayed);
    char    getNbPawnsPlayed();
    void    setPlayers(string playerL, string playerR);
    string  getPlayers();
    string  getPlayerL();
    string  getPlayerR();
    FILE*   getRules();
    bool    swapRule();
    bool    continueGame();
    void    displayBoard();
    bool    setPosition(char x, char y, char v);
    bool    pawnConnected(char x, char y);
    bool    victoryBySide(char p);
};

#endif // HEXBOARD_H
