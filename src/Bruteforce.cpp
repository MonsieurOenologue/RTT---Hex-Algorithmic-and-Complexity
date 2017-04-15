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

    if(first) generatePlayer1RecursiveMovesTree(boardTemp, pos);
    else generatePlayer2RecursiveMovesTree(boardTemp, pos);
    cerr << "WinningMoves#" << movesTree.size() << endl;

    if(first)
        for(i = 0, j = 0; j < badMoves.size(); ++j) {
            for(proc = false; i < movesTree.size(); ++i) {
                //cerr << "processing..." << endl;
                toPrint("movesTree :", movesTree[i]);
                if(badMoves[j].compare(movesTree[i].substr(0, badMoves[j].size())) == 0) {
                    proc = true;
                    toPrint("badMove :", movesTree[i+1]);
                    cin.sync(); cin.get();
                    movesTree.erase(movesTree.begin() + i); /// Getting ride of bad moves sequence
                    i--;
                } else if(proc) break;
            }
            //cerr << "Done#" << j+0 << endl;
            //cerr << "Remains#" << movesTree.size() << endl;
            //cin.sync(); cin.get();
        }
}

/*Profondeur : p
Si une solution est trouvee en p : inutile de parcourir en p+1
Si aucune branche p+1 ne gagne : on supprime la branche p (ex : p+1 = [0 2])
Si plusieurs coups n'influent pas sur le resultat : les regrouper (ex : p1 = [1 0 2], p2 = [1 0 3]; p = [1 0 {2,3}])
Si un groupe n'omet aucun coup : le supprimer (ex : p = [1 0 {2,3}]; p' = [1 0])
Si un groupe n'omet qu'un seul coup : le transformer en "non" logique (ex : p1 = [1 2 3], p2 = [1 3 2], p' = [1 !0 !0])
Si plusieurs solutions englobent toutes les possibilites : les fusionner (ex : p1 = [1 0], p2 = [1 !0 !0], p' = [1 !0 !0])
*/

bool Bruteforce::generatePlayer1RecursiveMovesTree(Action boardTemp, ustring pos) {
    unsigned char i, _size = pos.size(), alreadyLost = 0;
    bool AIplaying = first ^ (boardTemp.getPlayerPawn() == 'o');
    ustring tmp;

    for(i = 0; i < _size; ++i) {
        if(boardTemp.setPosition(pos[i])) {
            if(boardTemp.continueGame()) {
                tmp = pos;
                tmp.erase(tmp.find_first_of(tmp[i]), 1); /// Getting ride of played move
                if(generatePlayer1RecursiveMovesTree(boardTemp, tmp)) { /// AI lost on next move
                    alreadyLost++;
                }
            } else if(AIplaying) { /// AI win
                movesTree.push_back(boardTemp.getMovesTree());
                //if(!random) return false; /// Avoid multiple moves for the same solution
            } else return true; /// Avoid hoping for missplay(s) (only for player 1)
            if(!boardTemp.undoMove()) cerr << "Error : No move to undo." << endl;
        } else {
            cerr << "Error : Unexpected position " << pos[i]+0;
            toPrint(" on moves", boardTemp.getMovesTree());
        }
    }

    if(alreadyLost == _size) {
        tmp = boardTemp.getMovesTree();
        tmp.pop_back();
        if(tmp.empty()) return true;
        if(badMoves.empty()) {
            /*toPrint("badMove :", tmp);
            cin.sync(); cin.get();*/
            badMoves.push_back(tmp);
            return true;
        }
        if(tmp.size() >= badMoves[badMoves.size()-1].size() && tmp.substr(0, badMoves[badMoves.size()-1].size()).compare(badMoves[badMoves.size()-1]) != 0) {
            /*toPrint("badMove :", tmp);
            cin.sync(); cin.get();*/
            badMoves.push_back(tmp);
            return true;
        } else {
            for(i = 0; tmp.size() < badMoves[badMoves.size()-1].size() && badMoves[badMoves.size()-1].substr(0, tmp.size()).compare(tmp) == 0; ++i) {
                /*toPrint("depop :", badMoves[badMoves.size()-1]);
                cin.sync(); cin.get();*/
                badMoves.pop_back();
            }
            if(i == 0 && tmp.size() >= badMoves[badMoves.size()-1].size()) return true;
            /*toPrint("badMove :", tmp);
            cin.sync(); cin.get();*/
            badMoves.push_back(tmp);
        }
        return true;
    }

    return false;
}

bool Bruteforce::generatePlayer2RecursiveMovesTree(Action boardTemp, ustring pos) {
    unsigned char i, _size = pos.size(), alreadyLost = 0, soonLost = 0, canWin = 0;
    bool AIplaying = first ^ (boardTemp.getPlayerPawn() == 'o');
    ustring tmp;

    for(i = 0; i < _size; ++i) {
        if(boardTemp.setPosition(pos[i])) {
            if(boardTemp.continueGame()) {
                tmp = pos;
                tmp.erase(tmp.find_first_of(tmp[i]), 1); /// Getting ride of played move
                if(generatePlayer2RecursiveMovesTree(boardTemp, tmp)) { /// AI lost on next move
                    toPrint("badMove :", boardTemp.getMovesTree());
                    soonLost++;
                } else canWin++;
            } else if(AIplaying) { /// AI win
                canWin++;
                movesTree.push_back(boardTemp.getMovesTree());
                //if(!random) return false; /// Avoid multiple moves for the same solution
            } else alreadyLost++; /// AI lose
            //} else return true; /// Avoid hoping for missplay(s) (doesn't work for player 2)
            if(!boardTemp.undoMove()) cerr << "Error : No move to undo." << endl;
        } else {
            cerr << "Error : Unexpected position " << pos[i]+0;
            toPrint(" on moves", boardTemp.getMovesTree());
        }
    }

    if(first && alreadyLost + soonLost == _size) {
        tmp = boardTemp.getMovesTree();
        tmp.pop_back();
        if(tmp.size() != 0) {
            toPrint("badSequence :", tmp);
            badMoves.push_back(tmp);
        }
        return true;
    } else if(!first && (alreadyLost != 0 || canWin == 0)) {
        cout << "(a" << alreadyLost+0 << ", s" << soonLost+0 << ", c" << canWin+0 << ")" << endl;
        tmp = boardTemp.getMovesTree();
        //tmp.pop_back();
        if(tmp.size() != 0) {
            toPrint("badSequence#2 :", tmp);
            badMoves.push_back(tmp);
        }
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
    cerr << "Il y a " << movesTree.size() << " solutions." << endl;
    for(i = 0; i < movesTree.size(); ++i) {
        for(j = 0; j < movesTree[i].size(); ++j) {
            cout << movesTree[i][j]+0 << " ";
        }
        cout << endl;
    }
}
