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

char Action::getLatestMove() {
    char latestMove = movesTree[movesTree.size()-1];
    movesTree.resize(movesTree.size()-1);
    return latestMove;
}

bool Action::nextMove(char x, char y, char v) {
    bool newPos = setPosition(x, y, v);
    if(newPos) movesTree.push_back(x * getLength() + y);
    return newPos;
}

bool Action::undoMove() {
    if(movesTree.size() < 1) return false;
    setPosition(movesTree[movesTree.size()-1] / getLength(), movesTree[movesTree.size()-1] % getLength(), ' ');
    return true;
}
