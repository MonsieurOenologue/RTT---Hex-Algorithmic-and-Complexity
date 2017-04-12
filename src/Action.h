#ifndef ACTION_H
#define ACTION_H

#include "HexBoard.h"

class Action : public HexBoard {
private :

public :
                    Action();
                    Action(unsigned char newLength);
                    ~Action();
    void            giveUp();
    bool            nextMove();
    bool            undoMove();
};

#endif // ACTION_H
