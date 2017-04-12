#ifndef ACTION_H
#define ACTION_H

#include "HexBoard.h"

class Action : public HexBoard {
private :

public :
                    Action();
                    Action(unsigned char);
                    ~Action();
    void            giveUp();
    bool            nextMove(unsigned char);
    bool            undoMove();
};

#endif // ACTION_H
