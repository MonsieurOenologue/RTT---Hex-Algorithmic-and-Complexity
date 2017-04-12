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

Bruteforce::Bruteforce() {}

void toPrint(const char* message, ustring datas) {
    cout << message;
    for(unsigned int i = 0; i < datas.size(); ++i) {
        cout << " " << (datas[i]+0);
    }
    cout << endl;
}

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
void Bruteforce::generateMovesTree(unsigned char length, bool player1, bool randomize) {
    unsigned long long complexity = 2, alreadyFound = 0, i, j;
    for(i = 3; i <= length * length; ++i) complexity *= i; // factor
    unsigned char x, y, v = 'x', cost = 0, separator = 255, print;
    ustring toStore;
    bool solved = false;
    Action boardTemp;

    boardTemp.setLength(length);
    random = randomize;
    first = (player1) ? true : false;
    toStore.clear();
    movesTree.clear();

    while(complexity > 0) {
        for(x = 0; x < length; ++x) {
            for(y = 0; y < length; ++y) {
                if(boardTemp.setPosition(x, y, v)) {
                    if(boardTemp.victoryByRecursion(x, y, v)) {
                        toStore = boardTemp.getMovesTree();
                        toPrint("Solution :", toStore);
                        for(i = 0; i < movesTree.size(); ++i) {
                            toPrint("movesTree[i] =", movesTree[i]);
                            if(movesTree[i].find(toStore) != ustring::npos) {
                                alreadyFound++;
                                for(j = 0; j <= alreadyFound; ++j) {
                                    if(!boardTemp.undoMove()) cerr << "No move to undo." << endl;
                                    v ^= 'x'^'o';
                                }
                                break;
                            }
                        }
                        if(alreadyFound != 0) continue;
                        cin.sync();
                        cin.get();
                        solved = true;
                        alreadyFound = 0;
                        /// player win <==> AI lose
                        /*if((v == 'x') ^ first) {
                            toStore += separator + cost;
                        } else {
                            toStore += separator + (cost + 1);
                        }*/
                        movesTree.push_back(toStore);
                        if(!boardTemp.undoMove()) cerr << "No move to undo." << endl;
                    }
                    v ^= 'x'^'o';
                }
            }
        }
        if(solved) {
            complexity--;
            solved = false;
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
    ustring locate;
    for(i = 0; i < movesTree.size(); ++i) {
        locate = currentBoardState.getMovesTree();
        if(movesTree[i].find(locate) != ustring::npos) {
            //t = movesTree[i].back();
            tmp = movesTree[i][movesTree[i].size()-2];
            //if(mini > t) {
                //mini = t;
                //p = tmp;
                if(t == 0) break;
            //}
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
