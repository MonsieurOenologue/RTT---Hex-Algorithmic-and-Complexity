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
    for(unsigned char i = 0; i < datas.size(); ++i) {
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
    unsigned char x, y, maxPawns = length * length;
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

void Bruteforce::generateRecursiveMovesTree(unsigned char length, bool player1, bool randomize) {
    unsigned char i, j, maxPawns = length * length;
    Action boardTemp(length);
    ustring pos;
    pos.clear();
    bool proc;

    for(i = 0; i < maxPawns; ++i) pos += i;

    first = (player1) ? true : false;
    random = randomize;
    movesTree.clear();
    badMoves.clear();

    generateRecursiveMovesTree(boardTemp, pos);

    for(i = 0, j = 0; j < badMoves.size(); ++j) {
        for(proc = false; i < movesTree.size(); ++i) {
            //cerr << "processing..." << endl;
            if(badMoves[j].compare(movesTree[i].substr(0, badMoves[j].size())) == 0) {
                proc = true;
                //toPrint("badMove :", movesTree[i]);
                movesTree.erase(movesTree.begin() + i); /// Getting ride of bad moves sequence
                i--;
            } else if(proc) break;
        }
        //cerr << "Done#" << j+0 << endl;
        //cerr << "Remains#" << movesTree.size() << endl;
        //cin.sync(); cin.get();
    }
}

bool Bruteforce::generateRecursiveMovesTree(Action boardTemp, ustring pos) {
    unsigned char i, _size = pos.size(), alreadyLost = 0;
    bool AIplaying = first ^ (boardTemp.getPlayerPawn() == 'o');
    ustring tmp;

    for(i = 0; i < _size; ++i) {
        if(boardTemp.setPosition(pos[i])) {
            if(boardTemp.continueGame()) {
                tmp = pos;
                tmp.erase(tmp.find_first_of(tmp[i]), 1); /// Getting ride of played move
                if(generateRecursiveMovesTree(boardTemp, tmp)) { /// AI lost on next move
                    alreadyLost++;
                }
            } else if(AIplaying) { /// AI win
                movesTree.push_back(boardTemp.getMovesTree());
            } else return true; /// AI lose
            if(!boardTemp.undoMove()) cerr << "Error : No move to undo." << endl;
        } else {
            cerr << "Error : Unexpected position " << pos[i]+0;
            toPrint(" on moves", boardTemp.getMovesTree());
        }
    }

    if(alreadyLost == _size) {
        tmp = boardTemp.getMovesTree();
        tmp.pop_back();
        //toPrint("badSequence :", tmp);
        badMoves.push_back(tmp);
        return true;
    }

    return false;
}

Bruteforce::~Bruteforce() {}

bool Bruteforce::getFirst() {
    return first;
}

bool Bruteforce::playNextMove(Action &currentBoardState) {
    unsigned char nbPawnsPlayed = currentBoardState.getNbPawnsPlayed(), maxNbPawns = currentBoardState.getMaxNbPawns(), pos;
    unsigned long long i, _size = movesTree.size();

    if(nbPawnsPlayed == 0)
        return currentBoardState.setPosition(movesTree[rand() % _size][0]);
    if(nbPawnsPlayed >= maxNbPawns)
        return false;

    srand(time(NULL));
    ustring locate = currentBoardState.getMovesTree();

    for(i = 0; i < _size; ++i) {
        if(locate.compare(movesTree[i].substr(0, locate.size())) == 0) {
            pos = movesTree[i][locate.size()];
            if(currentBoardState.setPosition(pos)) return true;
        }
    }
    while(!currentBoardState.setPosition(rand() % maxNbPawns));
    return true;
}

void Bruteforce::displayMovesTree() {
    unsigned long long i, j;
    cerr << "movesTree.size() = " << movesTree.size() << endl;
    for(i = 0; i < movesTree.size(); ++i) {
        for(j = 0; j < movesTree[i].size(); ++j) {
            cout << movesTree[i][j]+0 << " ";
        }
        cout << endl;
    }
}
