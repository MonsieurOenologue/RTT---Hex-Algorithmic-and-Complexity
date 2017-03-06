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
    path = 0;
    latestMove = '\0';
    for(char i = 0; i < 11; ++i) {
        board[i] = string(11, ' ');
    }
}

HexBoard::HexBoard(char newLength) {
    length = newLength;
    nbPawnsPlayed = 0;
    board.resize(newLength);
    path = 0;
    latestMove = '\0';
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
    path = 0;
    char x = ceil(latestMove / length), y = latestMove % length;
    return winConditionRecursive(x,y);
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
    latestMove = x * length + y;
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

bool HexBoard::winConditionRecursive(char line, char col) {
    return (board[line][col] == ' ') ? true : (winConditionRecursive(line,col,board[line][col],path) != 3);
}

char HexBoard::winConditionRecursive(char line, char col, char j, char p) {
    if(p%3 != 1 && board[line][col] == j && line == 0 ) {
        p+=1;
    } else if(p%3 != 2 && board[line][col] == j && line == length-1 ) {
        p+=2;
    }
    if(p==3) return p;
    board[line][col] -= 2;
    if(line != 0 && col != 0 && board[line-1][col-1] == j) {
        p = winConditionRecursive(line-1,col-1,j,p);
    }
    if(p!=3 && line != 0 && board[line-1][col] == j) {
        p = winConditionRecursive(line-1,col,j,p);
    }
    if(p!=3 && line + 1 != length && board[line+1][col] == j) {
        p = winConditionRecursive(line+1,col,j,p);
    }
    if(p!=3 && line + 1 != length && col+1 != length && board[line+1][col+1] == j)  {
        p = winConditionRecursive(line+1,col+1,j,p);
    }
    if(p!=3 && col != 0 && board[line][col-1] == j) {
        p = winConditionRecursive(line,col-1,j,p);
    }
    if(p!=3 && col + 1 != length && board[line][col+1] == j) {
        p = winConditionRecursive(line,col+1,j,p);
    }

    board[line][col] += 2;

    return p;
}
