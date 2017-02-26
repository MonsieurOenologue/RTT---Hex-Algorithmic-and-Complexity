#include "hexBoard.h"

hexBoard::hexBoard() {
    length = 11;
    board.resize(11);
    for(char i = 0; i < 11; ++i) {
        board[i] = string(11, ' ');
    }
}

hexBoard::hexBoard(char newLength) {
    length = newLength;
    board.resize(newLength);
    for(char i = 0; i < newLength; ++i) {
        board[i] = string(newLength, ' ');
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

bool hexBoard::continueGame() {
    return true;
}

void hexBoard::displayBoard() {
    string flatI = "";
    unsigned char i, j, c = 'A', l = 'a';
    cout << endl << ' ';
    for(i = 0; i < board.size(); ++i) {
        cout << ' ' << c;
        c++;
    }
    cout << endl;
    for(i = 0; i < board.size(); ++i) {
        cout << flatI << l << '\\';
        for(j = 0; j < board[i].size(); ++j) {
            cout << board[i][j] << '\\';
        }
        cout << l << endl;
        flatI += ' ';
        l++;
    }
    c -= board.size();
    flatI += ' ';
    cout << flatI;
    for(i = 0; i < board.size(); ++i) {
        cout << ' ' << c;
        c++;
    }
    cout << endl << endl;
}

void hexBoard::setPosition(char x, char y, char v) {
    if(x < 0 || x > length || y < 0 || y > length) return;
    board[x][y] = v;
}
