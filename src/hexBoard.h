#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class HexBoard {
private :
    char            length;
    string          players;
    vector<string>  board;

public :
            HexBoard();
            HexBoard(char newLength);
            ~HexBoard();
    void    setLength(char newLength);
    char    getLength();
    void    setPlayers(string playerL, string playerR);
    string  getPlayers();
    string  getPlayerL();
    string  getPlayerR();
    FILE*   getRules();
    bool    swapRule();
    bool    continueGame();
    void    displayBoard();
    bool    setPosition(char x, char y, char v);
};

#endif // HEXBOARD_H
