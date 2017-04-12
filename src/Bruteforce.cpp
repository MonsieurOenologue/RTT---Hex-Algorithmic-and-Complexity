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
    unsigned char x, y, cost = 0, separator = 255, maxPawns = length * length;
    unsigned long long complexity = 2, i, backtrack = 0;
    for(i = 3; i <= maxPawns; ++i) complexity *= i; // factor
    ustring toStore;
    Action boardTemp(length);

    random = randomize;
    first = (player1) ? true : false;
    toStore.clear();
    movesTree.clear();

    while(complexity > 0) {
        for(x = 0; x < length; ++x) {
            for(y = 0; y < length; ++y) {
                if(boardTemp.setPosition(x, y)) {
                    toStore = boardTemp.getMovesTree();
                    toPrint("Current movesTree :", toStore);
                    cout << "movesTree size = " << movesTree.size() << endl;
                    for(i = 0; i < movesTree.size(); ++i) {
                        toPrint("movesTree[i] :", movesTree[i]);
                        if(toStore.compare(movesTree[i].substr(0, toStore.size())) == 0) {
                            cout << "Already founded!" << endl;
                            cin.sync(); cin.get();
                            backtrack++;
                            break;
                        }
                    }
                    if(backtrack != 0 && i != movesTree.size()) {
                        for(i = 0; i < backtrack; ++i)
                            if(!boardTemp.undoMove()) cerr << "No move to undo.#0" << endl;
                            else cout << "UndoMove" << endl;
                        continue;
                    }
                    cout << "Keep going...";
                    cin.sync(); cin.get();
                    if(boardTemp.getNbPawnsPlayed() == maxPawns) {
                    //if(boardTemp.victoryByRecursion(x, y)) {
                        toPrint("Solution :", toStore);
                        complexity--;
                        backtrack = 0;
                        /// player win <==> AI lose
                        /*if((v == 'x') ^ first) {
                            toStore += separator + cost;
                        } else {
                            toStore += separator + (cost + 1);
                        }*/
                        movesTree.push_back(toStore);
                        if(!boardTemp.undoMove()) cerr << "No move to undo.#1" << endl;
                        /*else {
                            if(y == 0) {
                                y = length - 1;
                                x = (x == 0) ? length - 1 : x - 1;
                            } else y--;
                            cout << "x = " << x+0 << ", y = " << y+0 << endl;
                        }*/
                    }
                }
            }
        }
    }
}

Bruteforce::~Bruteforce() {}

bool Bruteforce::getFirst() {
    return first;
}

bool Bruteforce::playNextMove(Action &currentBoardState) {
    unsigned long long i;
    unsigned char t = 0, p = 255, /*mini = 255,*/ tmp, length = currentBoardState.getLength();
    ustring locate;
    for(i = 0; i < movesTree.size(); ++i) {
        locate = currentBoardState.getMovesTree();
        if(movesTree[i].find(locate) != ustring::npos) {
            //t = movesTree[i][movesTree[i].size() - 1];
            tmp = movesTree[i][movesTree[i].size() - 1];
            //if(mini > t) {
                //mini = t;
                p = tmp;
                if(t == 0) break;
            //}
        }
    }
    return (currentBoardState.setPosition(ceil(p / length), p % length)) ? true : false;
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
