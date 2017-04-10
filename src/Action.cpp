#include "Action.h"

/**
 *  @file    Action.cpp
 *  @author  RTT
 *  @date    25/02/2017
 *  @version 1.0
 *
 *  @brief
 *
 *  @section DESCRIPTION
 *
 */
Action::Action() {
    movesTree.clear();
}

Action::~Action() {
    movesTree.clear();
}

void Action::giveUp() {}

vector<char> Action::getMovesTree() {
    return movesTree;
}

char Action::pullLatestMove() {
    char latestMove = movesTree[movesTree.size()-1];
    movesTree.resize(movesTree.size()-1);
    return latestMove;
}

bool Action::nextMove(char v) {
    char x = 0, y = 0;
    cin >> y >> x;
    while(y < 65 || x < 97 || y > 64 + getLength() || x > 96 + getLength()) {
        cout << "Coup impossible, veuillez recommencer : ";
        cin >> y >> x;
    }
    x -= 97;
    y -= 65;
    bool newPos = setPosition(x, y, v);
    if(!newPos) {
        cout << "Coup impossible, veuillez recommencer : ";
        return nextMove(v);
    } else movesTree.push_back(x * getLength() + y);
    return newPos;
}

bool Action::undoMove() {
    if(movesTree.size() < 1) return false;
    setPosition(movesTree[movesTree.size()-1] / getLength(), movesTree[movesTree.size()-1] % getLength(), ' ');
    return true;
}
