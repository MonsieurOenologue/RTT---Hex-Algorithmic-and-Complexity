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
    random = false;
}

Bruteforce::~Bruteforce() {
    player1.clear();
    player2.clear();
}

void toPrint(const char* message, ustring datas) {
    cout << message;
    for(unsigned char i = 0; i < datas.size(); ++i) {
        cout << " " << (datas[i]+0);
    }
    cout << endl;
}

void toPrint(const char* message, vector<ustring> datas) {
    cout << message << endl;
    unsigned char i, j;
    for(i = 0; i < datas.size(); ++i) {
        for(j = 0; j < datas[i].size(); ++j) {
            cout << (datas[i][j]+0) << " ";
        }
        cout << endl;
    }
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

void Bruteforce::generateMovesTree(unsigned char length, bool randomize) {
    if(generated) return;

    unsigned char i, maxNbPawns = length * length;
    Action boardTemp(length);
    ustring pos;
    pos.clear();

    for(i = 0; i < maxNbPawns; ++i) pos += i;

    random = randomize;
    player1.clear();
    player2.clear();

    generateMovesTree(boardTemp, pos);
    cerr << "WinningMovesP1#" << player1.size() << endl;
    toPrint("Moves P1 :", player1);
    cerr << "WinningMovesP2#" << player2.size() << endl;
    toPrint("Moves P2 :", player2);

    sortPlayer1(1); /// TO DO : determine maxBranchLength from generate function, avoid comparing different moves length

    generated = true;
}

/**Profondeur : p
Si une solution est trouvee en p : inutile de parcourir en p+1
Si aucune branche p+1 ne gagne : on supprime la branche p (ex : p+1 = [0 2])
Si plusieurs coups n'influent pas sur le resultat : les regrouper (ex : p1 = [1 0 2], p2 = [1 0 3]; p = [1 0 {2,3}])
Si un groupe n'omet aucun coup : le supprimer (ex : p = [1 0 {2,3}]; p' = [1 0])
Si un groupe n'omet qu'un seul coup : le transformer en "non" logique (ex : p1 = [1 2 3], p2 = [1 3 2], p' = [1 !0 !0])
Si plusieurs solutions englobent toutes les possibilites : les fusionner (ex : p1 = [1 0], p2 = [1 !0 !0], p' = [1 !0 !0])
**/

void Bruteforce::generateMovesTree(Action boardTemp, ustring pos) {
    unsigned char i, _size = pos.size(), player2Won = 0;
    bool player1Move = (boardTemp.getPlayerPawn() == 'x');
    ustring tmp;

    for(i = 0; i < _size; ++i) {
        if(boardTemp.setPosition(pos[i])) {
            if(boardTemp.continueGame()) {
                tmp = pos;
                tmp.erase(tmp.find_first_of(tmp[i]), 1); /// Getting ride of played move
                generateMovesTree(boardTemp, tmp);
            } else if(player1Move) { /// AI P1 win
                player1.push_back(boardTemp.getMovesTree());
            } else player2Won++; /// AI P2 win
            if(!boardTemp.undoMove()) cerr << "Error : No move to undo." << endl;
        } else {
            cerr << "Error : Unexpected position " << pos[i]+0;
            toPrint(" on moves", boardTemp.getMovesTree());
        }
    }

    if(player2Won != 0) {
        tmp = boardTemp.getMovesTree();
        tmp.pop_back();
        player2.push_back(tmp);
    }
}

void Bruteforce::sortPlayer1(unsigned char maxBranchLength) {
    unsigned char i, j, k, cpt, MinMax;
    ustring old, tmp;
    vector<ustring> pawns;

    for(k = 1; k <= maxBranchLength; ++k) {
        old.clear();
        tmp.clear();
        pawns.clear();
        for(i = 0, cpt = 1, MinMax = 0, old.push_back(255), pawns.push_back(old); i < player1.size(); ++i, ++cpt) {
            tmp = player1[i].substr(0, k);
            if(old.compare(tmp) != 0) {
                old = tmp;
                cpt = 1;
            }
            for(j = 0; j < pawns.size(); ++j) {
                if(pawns[j].compare(tmp) != 0) {
                    if(MinMax == cpt) { /// Handle multiple winning moves
                        pawns.push_back(tmp);
                    } else if(k % 2 == 1 && MinMax < cpt) {
                        pawns.clear();
                        pawns.push_back(tmp);
                        MinMax = cpt;
                        cpt = 0;
                    } else if(k % 2 == 0 && MinMax > cpt) {
                        pawns.clear();
                        pawns.push_back(tmp);
                        MinMax = cpt;
                        cpt = 0;
                    }
                    break;
                }
            }
            if(j == pawns.size()) MinMax++;
        }
        for(i = 0; i < player1.size(); ++i) {
            tmp = player1[i].substr(0, k);
            for(j = 0; j < pawns.size(); ++j) {
                if(tmp == pawns[j]) break;
            }
            if(j == pawns.size()) {
                player1.erase(player1.begin() + i);
                i--;
            }
        }
    }
}

bool Bruteforce::playNextMove(Action &currentBoardState) {
    unsigned char nbPawnsPlayed = currentBoardState.getNbPawnsPlayed(), maxNbPawns = currentBoardState.getMaxNbPawns(), pos;
    bool isPlayer1 = (nbPawnsPlayed % 2 == 0);
    unsigned long long i, _size = (isPlayer1) ? player1.size() : player2.size();

    if(nbPawnsPlayed == 0)
        return currentBoardState.setPosition(player1[rand() % _size][0]);
    if(nbPawnsPlayed == maxNbPawns)
        return false;

    srand(time(NULL));
    ustring locate = currentBoardState.getMovesTree();

    if(isPlayer1) {
        for(i = 0; i < _size; ++i) {
            if(locate.compare(player1[i].substr(0, locate.size())) == 0) {
                pos = player1[i][locate.size()];
                if(currentBoardState.setPosition(pos)) return true;
            }
        }
    } else {
        for(i = 0; i < _size; ++i) {
            if(locate.compare(player2[i].substr(0, locate.size())) == 0) {
                pos = player2[i][locate.size()];
                if(currentBoardState.setPosition(pos)) return true;
            }
        }
    }
    while(!currentBoardState.setPosition(rand() % maxNbPawns));
    return true;
}

void Bruteforce::displayPlayer1MovesTree() {
    unsigned long long i, j;
    cerr << "Il y a " << player1.size() << " solutions." << endl;
    for(i = 0; i < player1.size(); ++i) {
        for(j = 0; j < player1[i].size(); ++j) {
            cout << player1[i][j]+0 << " ";
        }
        cout << endl;
    }
}

void Bruteforce::displayPlayer2MovesTree() {
    unsigned long long i, j;
    cerr << "Il y a " << player2.size() << " solutions." << endl;
    for(i = 0; i < player2.size(); ++i) {
        for(j = 0; j < player2[i].size(); ++j) {
            cout << player2[i][j]+0 << " ";
        }
        cout << endl;
    }
}
