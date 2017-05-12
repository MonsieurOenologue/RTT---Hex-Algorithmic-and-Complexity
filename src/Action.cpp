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

Action::Action(unsigned char newLength) {
    setLength(newLength);
}

Action::~Action() {}

bool Action::nextMove() {
    unsigned char x = 0, y = 0;
    cin >> y >> x;
    while(y < 65 || x < 97 || y > 64 + getLength() || x > 96 + getLength()) {
        cout << "Coup impossible, veuillez recommencer : ";
        cin >> y >> x;
    }
    if(setPosition(x-97, y-65)) return true;
    cout << "Coup impossible, veuillez recommencer : ";
    return nextMove();
}

bool Action::undoMove() {
    return resetLatestPosition();
}
