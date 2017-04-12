#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <iostream>

using namespace std;

class GameView {
private :


public :
            GameView();
            ~GameView();
    void    newGame();
    bool    openGame(int);
    bool    saveGame();
};

#endif // GAMEVIEW_H
