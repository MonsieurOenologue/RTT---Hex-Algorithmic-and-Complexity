#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

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
