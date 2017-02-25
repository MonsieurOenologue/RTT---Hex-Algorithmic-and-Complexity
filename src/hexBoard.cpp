#include "hexBoard.h"

hexBoard::hexBoard() {
    board.resize(11);
    for(unsigned short i = 0; i < 11; ++i) {
        board[i] = string(11, '0');
    }
}

hexBoard::hexBoard(char newLength) {
    board.resize(newLength);
    for(unsigned short i = 0; i < board.size(); ++i) {
        board[i] = string(board.size(), '0');
    }
}

hexBoard::~hexBoard() {
    board.clear();
}

void hexBoard::setLength(char newLength) {
    length = newLength;
}

char hexBoard::getLength() {
    return length;
}

void hexBoard::setPlayers(string playerL, string playerR) {
    players = playerL + ";" + playerR;
}

string hexBoard::getPlayers() {
    return players;
}

string hexBoard::getPlayerL() {
    return players.substr(0, ';');
}

string hexBoard::getPlayerR() {
    return players.substr(players.find(';')+1, players.length());
}

FILE* hexBoard::getRules() {
    return NULL;
}

bool hexBoard::swapRule() {
    return false;
}

bool hexBoard::gameOver() {
    return false;
}

void hexBoard::displayBoard() {
    for(unsigned short i = 0; i < board.size(); ++i) {
        for(unsigned short j = 0; j < board[i].size(); ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
