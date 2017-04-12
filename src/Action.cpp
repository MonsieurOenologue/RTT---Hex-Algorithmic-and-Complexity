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
Action::Action() {}

Action::~Action() {}

void Action::giveUp() {}

bool Action::nextMove(unsigned char v) {
    unsigned char x = 0, y = 0;
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
    }
    return newPos;
}

bool Action::undoMove() {
    if(getNbPawnsPlayed() < 1) return false;
    unsigned char latestMove = pullLatestMove(), length = getLength();
    return resetPosition(ceil(latestMove / length), latestMove % length);
}
