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

Bruteforce::Bruteforce() {
    player1.clear();
    player2.clear();
    generated = false;
}

Bruteforce::~Bruteforce() {
    player1.clear();
    player2.clear();
}

bool Bruteforce::isGenerated() {
    return generated;
}

void Bruteforce::generateMovesTree(Action currentBoard) {
    if(generated) return;

    player1.clear();
    player2.clear();

    cout << "Chargement des solutions de Bruteforce..." << endl;

    generateMovesTree(currentBoard, player1, player2);

    cout << "Chargement termine." << endl
         << "Appuyez sur une touche pour continuer...";
    cin.sync();
    cin.get();

    generated = true;
}

unsigned char Bruteforce::generateMovesTree(Action boardTemp, vector<ustring> &solvedP1, vector<ustring> &solvedP2) {
    vector<ustring> tmpP1, tmpP2, solved, maybeP1, maybeP2;
    ustring pos = boardTemp.getPositions();
    bool player1Move = boardTemp.isPlayer1Turn();
    unsigned char i, _size = pos.size(), depth, minDepth = (player1Move) ? 255 : 0;

    for(i = 0; i < _size; ++i) {
        if(boardTemp.setPosition(pos[i])) {
            if(boardTemp.continueGame()) {
                if(player1Move) {
                    depth = generateMovesTree(boardTemp, tmpP1, tmpP2);
                    if(depth < minDepth) {
                        minDepth = depth;
                        maybeP1.clear();
                    }
                    if(depth == minDepth) {
                        maybeP1.insert(maybeP1.end(), tmpP1.begin(), tmpP1.end());
                    }
                    maybeP2.insert(maybeP2.end(), tmpP2.begin(), tmpP2.end());
                } else {
                    depth = generateMovesTree(boardTemp, tmpP1, tmpP2);
                    if(depth > minDepth) {
                        minDepth = depth;
                        maybeP1.clear();
                        maybeP2.clear();
                    }
                    if(depth == minDepth) {
                        maybeP1.insert(maybeP1.end(), tmpP1.begin(), tmpP1.end());
                        maybeP2.insert(maybeP2.end(), tmpP2.begin(), tmpP2.end());
                    }
                }
                tmpP1.clear();
                tmpP2.clear();
            } else solved.push_back(boardTemp.getMovesTree());
            if(!boardTemp.undoMove()) cerr << "Error : No move to undo." << endl;
        } else {
            cerr << "Error : Unexpected position " << pos[i]+0 << " on moves" << boardTemp.getMovesTree();
        }
    }

    if(solved.empty()) {
        solvedP1 = maybeP1;
        solvedP2 = maybeP2;
        return minDepth;
    } else if(player1Move) {
        solvedP1 = solved;
        solvedP2 = maybeP2;
        return boardTemp.getNbPawnsPlayed();
    } else {
        solvedP1 = maybeP1;
        solvedP2 = solved;
        return 255 - boardTemp.getNbPawnsPlayed();
    }
}

bool Bruteforce::playNextMove(Action &currentBoardState) {
    unsigned char nbPawnsPlayed = currentBoardState.getNbPawnsPlayed(), maxNbPawns = currentBoardState.getMaxNbPawns(), pos, lsize;
    bool isPlayer1 = currentBoardState.isPlayer1Turn(), solutionsFound = false;
    unsigned long long i, _size = (isPlayer1) ? player1.size() : player2.size();

    srand(time(NULL));
    if(nbPawnsPlayed == 0)
        return currentBoardState.setPosition(player1[rand() % _size][0]);
    if(nbPawnsPlayed == maxNbPawns)
        return false;

    ustring locate = currentBoardState.getMovesTree(), winningMoves;
    lsize = locate.size();
    winningMoves.clear();

    if(isPlayer1) {
        for(i = 0; i < _size; ++i) {
            if(lsize < player1[i].size() && locate.compare(player1[i].substr(0, lsize)) == 0) {
                solutionsFound = true;
                pos = player1[i][lsize];
                if(winningMoves.find_first_of(pos) == ustring::npos) winningMoves.push_back(pos);
            } else if(solutionsFound) break;
        }
        while(!winningMoves.empty()) {
            pos = winningMoves[rand() % winningMoves.size()];
            if(currentBoardState.setPosition(pos)) return true;
            else winningMoves.erase(winningMoves.find_first_of(pos), 1);
        }
    } else {
        for(i = 0; i < _size; ++i) {
            if(lsize < player2[i].size() && locate.compare(player2[i].substr(0, lsize)) == 0) {
                solutionsFound = true;
                pos = player2[i][lsize];
                if(winningMoves.find_first_of(pos) == ustring::npos) winningMoves.push_back(pos);
            } else if(solutionsFound) break;
        }
        while(!winningMoves.empty()) {
            pos = winningMoves[rand() % winningMoves.size()];
            if(currentBoardState.setPosition(pos)) return true;
            else winningMoves.erase(winningMoves.find_first_of(pos), 1);
        }
    }
    cout << "Joue un coup au hasard..." << endl;
    while(!currentBoardState.setPosition(rand() % maxNbPawns));
    return true;
}

void Bruteforce::displayNbMovesPlayer1() {
    cout << "Il y a " << player1.size() << " solutions pour le joueur1." << endl
         << "Appuyez sur une touche pour continuer...";
    cin.sync(); cin.get();
}

void Bruteforce::displayNbMovesPlayer2() {
    cout << "Il y a " << player2.size() << " solutions pour le joueur2." << endl
         << "Appuyez sur une touche pour continuer...";
    cin.sync(); cin.get();
}

void Bruteforce::displayPlayer1MovesTree() {
    unsigned int i;
    for(i = 0; i < player1.size(); ++i) {
        cout << player1[i] << endl;
    }
}

void Bruteforce::displayPlayer2MovesTree() {
    unsigned int i;
    for(i = 0; i < player2.size(); ++i) {
        cout << player2[i] << endl;
    }
}
