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
    nbPawnsPlayed = 0;
    board.resize(11);
    for(char i = 0; i < 11; ++i) {
        board[i] = string(11, ' ');
    }
}

HexBoard::HexBoard(char newLength) {
    length = newLength;
    nbPawnsPlayed = 0;
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

void HexBoard::setNbPawnsPlayed(char newNbPawnsPlayed) {
    nbPawnsPlayed = newNbPawnsPlayed;
}

char HexBoard::getNbPawnsPlayed() {
    return nbPawnsPlayed;
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
    nbPawnsPlayed++;
    return true;
}

bool HexBoard::pawnConnected(char x, char y) {
    char v = board[x][y];
    if(x != 0 && (board[x-1][y] == v || (y != length - 1 && board[x-1][y+1] == v))) {
        return true;
    }
    if(x != length - 1 && (board[x+1][y] == v || (y != 0 && board[x+1][y-1] == v))) {
        return true;
    }
    if(y != 0 && board[x][y-1] == v) {
        return true;
    }
    if(y != length - 1 && board[x][y+1] == v) {
        return true;
    }
    return false;
}

bool HexBoard::victoryBySide(char p) {
    char x = ceil(p / length), y = p % length, v = board[x][y];

    // TO DO : Insert current and linked pawns into matching var if connected to a side.
    if(v == 'x') {
        if(y == 0) {
            // Add links into highToLowSide
        } else if(y == length - 1) {
           // Add links into lowToHighSide
        } else if(pawnConnected(x, y) == 1) {
           // Add pawn into matching var, if both : victory
        }
    } else { // v == 'o'
        if(x == 0) {
            // Add links into leftToRightSide
        } else if(x == length - 1) {
            // Add links into rightToLeftSide
        } else if(pawnConnected(x, y) == 1) {
           // Add pawn into matching var, if both : victory
        }
    }

    // Number of pawns played is not significant enough to reach victory for both players.
    if(nbPawnsPlayed < length * 2 - 1) {
        return false;
    }

    // No victory found.
    return false;
}

bool HexBoard::winConditionRecursive(char abs, char ord, char p = 0) {
    if(board[abs][ord] == 'x') return winConditionRecursiveP1(abs,ord,p);
    else return winConditionRecursiveP2(abs,ord,p);
}


bool HexBoard::winConditionRecursiveP1(char abs, char ord, char p) {
    if(p==3) return true;
    if(p%3 == 2 && board[abs][0]=='x' && ord == 0 ) {
        p = 3;
        return true;
    }
    if(p%3 == 1 && board[abs][length-1]=='x' && ord == length-1 ) {
        p = 3;
        return true;
    }
    if(p%3 !=1 && board[abs][0]=='x' && ord == 0 ) {
        p+=1;
    }
    else if(p%3 !=2 && board[abs][length-1]=='x' && ord == length-1 ) {
        p+=2;
    }
    if(nbPawnsPlayed < length*2-1) return false;

    for(int i = abs-1; i<=abs+1; i++) {
        for(int j = ord-1; j <= ord+1; j++) {
            if(board[i][j] == 'x') return winConditionRecursiveP1(i,j,p);
        }
    }
    return false;
}

bool HexBoard::winConditionRecursiveP2(char abs, char ord, char p) {
    if(p==3) return true;
    if(p%3 == 2 && board[0][ord]=='o' && abs == 0 ) {
        p = 3;
        return true;
    }
    if(p%3 == 1 && board[length-1][ord]=='x' && abs == length-1 ) {
        p = 3;
        return true;
    }
    if(p%3 !=1 && board[0][ord]=='o' && abs == 0 ) {
        p+=1;
    }
    else if(p%3 !=2 && board[length-1][ord]=='o' && abs == length-1 ) {
        p+=2;
    }
    if(nbPawnsPlayed < length*2-1) return false;

    for(int i = abs-1; i<=abs+1; i++) {
        for(int j = ord-1; j <= ord+1; j++) {
            if(board[i][j] == 'o') return winConditionRecursiveP1(i,j,p);
        }
    }
    return false;
}

