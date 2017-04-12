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
    path = 0;
    movesTree.clear();
    initBoard();
}

HexBoard::HexBoard(unsigned char newLength) {
    length = newLength;
    nbPawnsPlayed = 0;
    path = 0;
    movesTree.clear();
    initBoard();
}

HexBoard::~HexBoard() {
    movesTree.clear();
    board.clear();
}

void HexBoard::initBoard() {
    board.resize(length);
    for(unsigned char i = 0; i < length; ++i) {
        board[i] = ustring(length, ' ');
    }
}

bool HexBoard::setLength(unsigned char newLength) {
    if(newLength < 2 || newLength > 15) return false;
    length = newLength;
    initBoard();
    return true;
}

unsigned char HexBoard::getLength() {
    return length;
}

void HexBoard::pushLatestMove(unsigned char newMove) {
    movesTree.push_back(newMove);
    nbPawnsPlayed++;
}

unsigned char HexBoard::getLatestMove() {
    return (nbPawnsPlayed == 0) ? 255 : movesTree[nbPawnsPlayed - 1];
}

unsigned char HexBoard::pullLatestMove() {
    if(nbPawnsPlayed == 0) return 255;
    nbPawnsPlayed--;
    unsigned char latestMove = movesTree[nbPawnsPlayed];
    movesTree.pop_back();
    return latestMove;
}

void HexBoard::setNbPawnsPlayed(unsigned char newNbPawnsPlayed) {
    nbPawnsPlayed = newNbPawnsPlayed;
}

unsigned char HexBoard::getNbPawnsPlayed() {
    return nbPawnsPlayed;
}

unsigned char HexBoard::getPlayerPawn() {
    return (nbPawnsPlayed % 2) ? 'o' : 'x';
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

ustring HexBoard::getMovesTree() {
    return movesTree;
}

FILE* HexBoard::getRules() {
    return NULL;
}

bool HexBoard::swapRule() {
    return false;
}

bool HexBoard::continueGame() {
    path = 0;
    unsigned char latestMove = getLatestMove();
    if(latestMove == 255) return true;
    unsigned char x = ceil(latestMove / length), y = latestMove % length;
    return !victoryByRecursion(x,y);
}

void HexBoard::displayBoard() {
    string flatI = "";
    unsigned char i, j, numbering = 'A';
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

bool HexBoard::setPosition(unsigned char x, unsigned char y) {
    unsigned char v = getPlayerPawn();
    if(x >= length || y >= length || v == ' ' || board[x][y] != ' ') return false;
    board[x][y] = v;
    pushLatestMove(x * length + y);
    return true;
}

bool HexBoard::resetPosition(unsigned char x, unsigned char y) {
    if(pullLatestMove() == 255 || x >= length || y >= length || board[x][y] == ' ') return false;
    board[x][y] = ' ';
    return true;
}

bool HexBoard::pawnConnected(unsigned char x, unsigned char y) {
    unsigned char v = board[x][y];
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

bool HexBoard::victoryByLinksMemory(unsigned char p) {
    unsigned char x = ceil(p / length), y = p % length, v = board[x][y];

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

bool HexBoard::victoryByRecursion(unsigned char x, unsigned char y) {
    if(board[x][y] == ' ') return false;
    return (victoryByRecursion(x, y, board[x][y]) == 3);
}

unsigned char HexBoard::victoryByRecursion(unsigned char x, unsigned char y, unsigned char p) {
    if(nbPawnsPlayed < length * 2 - 1) {
        return 0;
    }
    if(path != 3 && path % 3 != 1 && ((x == 0 && p == 'x') || (y == 0 && p == 'o'))) {
       path++;
    }
    if(path != 3 && path % 3 != 2 && ((x == length - 1 && p == 'x') || (y == length - 1 && p == 'o'))) {
       path += 2;
    }
    if(path == 3) {
        return path;
    }

    board[x][y]++;

    if(x != 0) {
        if(board[x-1][y] == p) {
            if((path = victoryByRecursion(x-1, y, p)) == 3) {
                board[x][y]--;
                return path;
            }
        }
        if(y+1 < length && board[x-1][y+1] == p) {
            if((path = victoryByRecursion(x-1, y+1, p)) == 3) {
                board[x][y]--;
                return path;
            }
        }
    }
    if(x + 1 != length) {
        if(board[x+1][y] == p) {
            if((path = victoryByRecursion(x+1, y, p)) == 3) {
                board[x][y]--;
                return path;
            }
        }
        if(y != 0 && board[x+1][y-1] == p) {
            if((path = victoryByRecursion(x+1, y-1, p)) == 3) {
                board[x][y]--;
                return path;
            }
        }
    }
    if(y != 0 && board[x][y-1] == p) {
        if((path = victoryByRecursion(x, y-1, p)) == 3) {
            board[x][y]--;
            return path;
        }
    }
    if(y + 1 != length && board[x][y+1] == p) {
        path = victoryByRecursion(x, y+1, p);
    }

    board[x][y]--;
    return path;
}
