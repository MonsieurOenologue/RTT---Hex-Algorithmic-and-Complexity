#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class hexBoard {
private :
    char            length;
    string          players;
    vector<string>  board;

public :
            hexBoard();
            hexBoard(char newLength);
            ~hexBoard();
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
    void    setPosition(char x, char y, char v);
};

#endif // HEXBOARD_H
