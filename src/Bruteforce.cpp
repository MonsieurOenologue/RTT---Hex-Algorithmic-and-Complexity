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

    unsigned char i, maxNbPawns = length * length;//, halfNbPawns = maxNbPawns >> 1;
    Action boardTemp(length);
    ustring pos;
    pos.clear();

    for(i = 0; i < maxNbPawns; ++i) pos += i; // Unordered
    // Order from center cells to angle ones
    /*for(i = 1; i <= halfNbPawns; ++i) {
        pos += halfNbPawns - i;
        pos += halfNbPawns + i - (halfNbPawns % 2 == 0);
    }*/

    random = randomize;
    player1.clear();
    player2.clear();

    cout << "Chargement des solutions de Bruteforce..." << endl;

    generateMovesTree(boardTemp, pos, player1, player2);

    cout << "Chargement termine." << endl
         << "Appuyez sur une touche pour continuer...";
    cin.sync();
    cin.get();

    generated = true;
}

/*vector<ustring> Bruteforce::generateOptimizedFirstMove(Action boardTemp, ustring pos) {
    unsigned char length = boardTemp.getLength(), pawn1, pawn2 = 255;
    ustring pos2 = pos;
    if(length % 2 == 0) {
        pawn1 = ((length * (length - 1)) >> 1);
        pawn2 = ((length * (length + 1)) >> 1) - 1;
    } else pawn1 = ((length * length) >> 1);
    boardTemp.setPosition(pawn1);
    pos.erase(pos.find_first_of(pawn1), 1);
    if(pawn2 == 255) return generateMovesTree(boardTemp, pos);
    vector<ustring> solutions = generateMovesTree(boardTemp, pos), temp;
    boardTemp.undoMove();
    boardTemp.setPosition(pawn2);
    pos2.erase(pos2.find_first_of(pawn2), 1);
    temp = generateMovesTree(boardTemp, pos2);
    solutions.insert(solutions.end(), temp.begin(), temp.end());
    return solutions;
}*/

/**Profondeur : p
Si une solution est trouvee en p : inutile de parcourir en p+1
Si aucune branche p+1 ne gagne : on supprime la branche p (ex : p+1 = [0 2])
Si plusieurs coups n'influent pas sur le resultat : les regrouper (ex : p1 = [1 0 2], p2 = [1 0 3]; p = [1 0 {2,3}])
Si un groupe n'omet aucun coup : le supprimer (ex : p = [1 0 {2,3}]; p' = [1 0])
Si un groupe n'omet qu'un seul coup : le transformer en "non" logique (ex : p1 = [1 2 3], p2 = [1 3 2], p' = [1 !0 !0])
Si plusieurs solutions englobent toutes les possibilites : les fusionner (ex : p1 = [1 0], p2 = [1 !0 !0], p' = [1 !0 !0])
**/

unsigned char Bruteforce::generateMovesTree(Action boardTemp, ustring pos, vector<ustring> &solvedP1, vector<ustring> &solvedP2) {
    vector<ustring> tmpP1, tmpP2, solved, maybeP1, maybeP2;
    ustring tmp;
    bool player1Move = boardTemp.isPlayer1Turn();
    unsigned char i, _size = pos.size(), depth, minDepth = (player1Move) ? 255 : 0;

    for(i = 0; i < _size; ++i) {
        if(boardTemp.setPosition(pos[i])) {
            if(boardTemp.continueGame()) {
                tmp = pos;
                tmp.erase(tmp.find_first_of(tmp[i]), 1); /// Getting ride of played move
                depth = generateMovesTree(boardTemp, tmp, tmpP1, tmpP2);
                if(player1Move) {
                    if(depth < minDepth) {
                        minDepth = depth;
                        maybeP1.clear();
                    }
                    if(depth == minDepth) {
                        maybeP1.insert(maybeP1.end(), tmpP1.begin(), tmpP1.end());
                    }
                    maybeP2.insert(maybeP2.end(), tmpP2.begin(), tmpP2.end());
                } else {
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
            cerr << "Error : Unexpected position " << pos[i]+0;
            toPrint(" on moves", boardTemp.getMovesTree());
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

void Bruteforce::displayPlayer1MovesTree() {
    unsigned long long i, j;
    cout << "Il y a " << player1.size() << " solutions pour le joueur1." << endl
         << "Appuyez sur une touche pour continuer...";
    cin.sync(); cin.get();
    for(i = 0; i < player1.size(); ++i) {
        for(j = 0; j < player1[i].size(); ++j) {
            cout << player1[i][j]+0 << " ";
        }
        cout << endl;
    }
}

void Bruteforce::displayPlayer2MovesTree() {
    unsigned long long i, j;
    cout << "Il y a " << player2.size() << " solutions pour le joueur2." << endl
         << "Appuyez sur une touche pour continuer...";
    cin.sync(); cin.get();
    for(i = 0; i < player2.size(); ++i) {
        for(j = 0; j < player2[i].size(); ++j) {
            cout << player2[i][j]+0 << " ";
        }
        cout << endl;
    }
}
