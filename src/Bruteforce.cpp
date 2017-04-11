#include "Bruteforce.h"
/**
 *  @file    Bruteforce.cpp
 *  @author  RTT
 *  @date    25/02/2017
 *  @version 1.0
 *
 *  @brief
 *
 *  @section DESCRIPTION
 *
 */
/*bool Bruteforce::Bruteforce() {
    vector<string> TMP = HexBoard.board;
    if(player == playerL) {
        for(char i = 0; i < HexBoard.nbPawnsPlayed; i++) {
            for(char j = 0; j < HexBoard.nbPawnsPlayed - i; j++){
                for(char x = 0; x < HexBoard.length; x++) {
                    for(char y = 0; y < HexBoard.length; y++) {
                        if(TMP[x][y] == ' ') {
                            if(!HexBoard.victoryByRecursion(x,y)) {
                            TMP[x][y] = x;
                            }
                        else setPosition(x,y,'x');
                        }

                    }
                }
            }
        }
    }
    else {for(char i = 0; i < HexBoard.nbPawnsPlayed; i++) {
            for(char j = 0; j < HexBoard.nbPawnsPlayed - i; j++){
                for(char x = 0; x < HexBoard.length; x++) {
                    for(char y = 0; y < HexBoard.length; y++) {
                        if(TMP[x][y] == ' ') {
                            if(!HexBoard.victoryByRecursion(x,y)) {
                            TMP[x][y] = x;
                            }
                        else setPosition(x,y,'o');
                        }

                    }
                }
            }
        }
    }

    }
}*/

/**maxi = length * length
Pour Evaluate(0 <= nbPawnsPlayed <= maxi)
    bestMove = infini
    Pour nbPawnsPlayed <= i <= maxi
        Si (!gameOver)
            nextMove j
            Si (IA == defeat <==> player == victory) bestMove = min(bestMove, j)
            //Sinon bestMove = Evaluate(nbPawnsPlayed + 1) /!\ Not calculated yet
            undoMove j
    MovesTree.add(nbPawnsPlayed, bestMove)
FinPour**/
/*Bruteforce::Bruteforce(unsigned char length, bool player1, bool randomize) {
    unsigned short maxPawns = length * length, i;
    unsigned char nbPawnsPlayed, bestMove, x, y, v;
    Action boardTemp;

    boardTemp.setLength(length);
    random = randomize;
    first = (player1) ? true : false;
    movesTree.clear();
    movesTree.resize(maxPawns);

    // set leaves of the movesTree
    for(nbPawnsPlayed = 0; nbPawnsPlayed <= maxPawns; ++nbPawnsPlayed) {
        // set player
        v = (player1 && first) 'x' : 'o';
        for(i = nbPawnsPlayed, bestMove = 255, x = 0, y = 0; i <= maxPawns; ++i) {
            while(!boardTemp.setPosition(x, y, v)) {
                if(y == length) {
                    x++;
                    y = 0;
                } else {
                    y++;
                }
            }
            // if player won <==> AI lose
            if(boardTemp.victoryByRecursion(x, y, v) && ((v == 'x' && !first) || (v == 'o' && first))) {
                index = movesTree[x * length + y].find(nbPawnsPlayed+':');
                if(index != string::npos) {

                }
                // add value
                movesTree[nbPawnsPlayed].push_back(1);
                // add move to minimize
                movesTree[nbPawnsPlayed].push_back(x * length + y);
            }
            // switch player
            v ^= 'x'^'o';
            boardTemp.undoMove();
        }
    }
    // set minimized moves of the movesTree
    for(nbPawnsPlayed = maxPawns - 1; nbPawnsPlayed >= 0; --nbPawnsPlayed) {
        for(i = 0; i < movesTree[nbPawnsPlayed].size(); ++i) {

        }
    }
}*/
Bruteforce::Bruteforce() {}

void Bruteforce::generateMovesTree(unsigned char length, bool player1, bool randomize) {
    unsigned long long complexity = 2, i, cpt, cpt2;
    unsigned short maxPawns = length * length;
    for(i = 3; i <= maxPawns; ++i) complexity *= i; // factor
    unsigned char x, y, v = 'x', t, m = 255;
    bool test;
    Action boardTemp;

    boardTemp.setLength(length);
    random = randomize;
    first = (player1) ? true : false;
    //v = (player1 && first) ? 'x' : 'o';
    movesTree.clear();
    movesTree.resize(complexity);

    for(x = 0, y = 0, cpt = 0, test = true, t = 0; movesTree.size() < complexity; ++y) {
        if(y == length) {
            x = (x + 1 == length) ? 0 : x + 1;
            y = 0;
        }
        if(boardTemp.setPosition(x, y, v)) {
            if(boardTemp.victoryByRecursion(x, y, v)) {
                // player win <==> AI lose
                t = ((v == 'x' && !first) || (v == 'o' && first)) ? 1 : 0;
                for(i = 0; i < movesTree.size(); ++i) {
                    // already found
                    if(movesTree[i].find(boardTemp.getMovesTree()) != string::npos) {
                        for(cpt2 = 0; cpt2 < cpt; ++cpt2) {
                            // switch player / AI
                            v ^= 'x'^'o';
                            boardTemp.undoMove();
                        }
                        cpt++;
                        test = false;
                        break;
                    }
                }
            }
            if(test) {
                movesTree.push_back(boardTemp.getMovesTree());
                movesTree.back().push_back(m);
                movesTree.back().push_back(t);
                cpt = 0;
            } else test = true;
            // switch player / AI
            v ^= 'x'^'o';
            boardTemp.undoMove();
        }
    }
}

Bruteforce::~Bruteforce() {}

bool Bruteforce::getFirst() {
    return first;
}

bool Bruteforce::playNextMove(Action &currentBoardState) {
    unsigned long long i;
    unsigned char t = 0, p = 255, mini = 255, tmp, length = currentBoardState.getLength(), v = 'x';
    string locate;
    for(i = 0; i < movesTree.size(); ++i) {
        locate = currentBoardState.getMovesTree();
        if(movesTree[i].find(locate) != string::npos) {
            t = movesTree[i].back();
            tmp = movesTree[i][movesTree[i].size()-3];
            if(mini > t) {
                mini = t;
                p = tmp;
                if(t == 0) break;
            }
        }
    }
    return (currentBoardState.setPosition(ceil(p / length), p % length, v)) ? true : false;
}

void Bruteforce::displayMovesTree() {
    unsigned long long i, j;
    for(i = 0; i < movesTree.size(); ++i) {
        for(j = 0; j+2 < movesTree[i].size(); ++j) {
            cout << movesTree[i][j]+0 << " ";
        }
        cout << "; " << movesTree[i][j+1]+0 << endl;
    }
}
