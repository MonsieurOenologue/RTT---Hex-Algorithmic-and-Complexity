#include "HexBoard.h"

/**
 *  @file    HexBoard.cpp
 *  @author  RTT
 *  @date    25/02/2017
 *  @version 1.0
 *
 *  @brief
 *
 *  @section DESCRIPTION
 *
 */
HexBoard::HexBoard() {
    length = 11;
    board.resize(11);
    for(char i = 0; i < 11; ++i) {
        board[i] = string(11, ' ');
    }
}

HexBoard::HexBoard(char newLength) {
    length = newLength;
    board.resize(newLength);
    for(char i = 0; i < newLength; ++i) {
        board[i] = string(newLength, ' ');
    }
}

HexBoard::~HexBoard() {
    board.clear();
}

void HexBoard::setLength(char newLength) {
    length = newLength;
}

char HexBoard::getLength() {
    return length;
}

void HexBoard::setPlayers(string playerL, string playerR) {
    players = playerL + ";" + playerR;
}

string HexBoard::getPlayers() {
    return players;
}

string HexBoard::getPlayerL() {
    return players.substr(0, ';');
}

string HexBoard::getPlayerR() {
    return players.substr(players.find(';')+1, players.length());
}

FILE* HexBoard::getRules() {
    return NULL;
}

bool HexBoard::swapRule() {
    return false;
}

bool HexBoard::continueGame() {
    return true;
}

void HexBoard::displayBoard() {
    string flatI = "";
    char i, j, numbering = 'A';
    cout << endl << ' ';
    for(i = 0; i < length; ++i) {
        cout << ' ' << numbering;
        numbering++;
    }
    cout << endl;
    numbering = 'a';
    for(i = 0; i < length; ++i) {
        cout << flatI << numbering << '\\';
        for(j = 0; j < length; ++j) {
            cout << board[i][j] << '\\';
        }
        cout << numbering << endl;
        flatI += ' ';
        numbering++;
    }
    numbering = 'A';
    flatI += ' ';
    cout << flatI;
    for(i = 0; i < length; ++i) {
        cout << ' ' << numbering;
        numbering++;
    }
    cout << endl << endl;
}

bool HexBoard::setPosition(char x, char y, char v) {
    if(x < 0 || x > length || y < 0 || y > length || (v != ' ' && board[x][y] != ' ')) return false;
    board[x][y] = v;
    return true;
}
