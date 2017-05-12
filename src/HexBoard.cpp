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
    maxNbPawns = length * length;
    path = 0;
    movesTree.clear();
    initBoard();
}

HexBoard::HexBoard(unsigned char newLength) {
    length = newLength;
    nbPawnsPlayed = 0;
    maxNbPawns = length * length;
    path = 0;
    movesTree.clear();
    initBoard();
}

HexBoard::~HexBoard() {
    movesTree.clear();
    positions.clear();
    board.clear();
}

void HexBoard::initBoard() {
    board.resize(length);
    positions.clear();
    for(unsigned char i = 0; i < maxNbPawns; ++i) {
        positions += i;
        if(i < length) board[i] = ustring(length, ' ');
    }
}

bool HexBoard::setLength(unsigned char newLength) {
    if(newLength < 2 || newLength > 15) return false;
    length = newLength;
    maxNbPawns = length * length;
    initBoard();
    return true;
}

unsigned char HexBoard::getLength() {
    return length;
}

void HexBoard::pushLatestMove(unsigned char newMove) {
    positions.erase(positions.find_first_of(newMove), 1); /// Getting ride of played move
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
    positions.push_back(latestMove); /// Push back unplayed move
    movesTree.pop_back();
    return latestMove;
}

unsigned char HexBoard::getNbPawnsPlayed() {
    return nbPawnsPlayed;
}

unsigned char HexBoard::getMaxNbPawns() {
    return maxNbPawns;
}

unsigned char HexBoard::getPlayerPawn() {
    return (nbPawnsPlayed % 2) ? 'o' : 'x';
}

bool HexBoard::isPlayer1Turn() {
    return (nbPawnsPlayed % 2 == 0);
}

bool HexBoard::isPlayer2Turn() {
    return (nbPawnsPlayed % 2);
}

void HexBoard::setPlayers(string playerL, string playerR) {
    players = playerL + ";" + playerR;
}

string HexBoard::getPlayers() {
    return players;
}

string HexBoard::getPlayerL() {
    if(players.empty() || players.find(';') == string::npos) return "PlayerL";
    return players.substr(0, players.find(';'));
}

string HexBoard::getPlayerR() {
    if(players.empty() || players.find(';') == string::npos || players.find(';')+1 >= players.size()) return "PlayerR";
    return players.substr(players.find(';')+1, players.size());
}

ustring HexBoard::getMovesTree() {
    return movesTree;
}

ustring HexBoard::getPositions() {
    return positions;
}

bool HexBoard::continueGame() {
    unsigned char latestMove = getLatestMove();
    if(latestMove == 255) return true;
    path = 0;
    return !victoryByRecursion(ceil(latestMove / length), latestMove % length);
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

bool HexBoard::emptyPosition(unsigned char pos) {
    unsigned char x = ceil(pos / length), y = pos % length;
    if(pos >= maxNbPawns || board[x][y] != ' ') return false;
    return true;
}

bool HexBoard::setPosition(unsigned char pos) {
    unsigned char x = ceil(pos / length), y = pos % length;
    if(pos >= maxNbPawns || board[x][y] != ' ') return false;
    board[x][y] = getPlayerPawn();
    pushLatestMove(pos);
    return true;
}

bool HexBoard::setPosition(unsigned char x, unsigned char y) {
    if(x >= length || y >= length || board[x][y] != ' ') return false;
    board[x][y] = getPlayerPawn();
    pushLatestMove(x * length + y);
    return true;
}

bool HexBoard::resetLatestPosition() {
    unsigned char latestMove = pullLatestMove();
    if(latestMove == 255) return false;
    board[ceil(latestMove / length)][latestMove % length] = ' ';
    return true;
}

bool HexBoard::victoryByRecursion(unsigned char x, unsigned char y) {
    if(board[x][y] == ' ' || nbPawnsPlayed < length * 2 - 1) return false;
    if(nbPawnsPlayed == maxNbPawns) return true;
    return (victoryByRecursion(x, y, board[x][y]) == 3);
}

unsigned char HexBoard::victoryByRecursion(unsigned char x, unsigned char y, unsigned char p) {
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
