#include "HexBoard.h"
#include "Action.h"

/**
 *  @file    GameController.cpp
 *  @author  RTT
 *  @date    25/02/2017
 *  @version 1.0
 *
 *  @brief
 *
 *  @section DESCRIPTION
 *
 */
void newGame() {
    Action moves;
    bool player1 = true;
    char x, y, randX, randY;
    srand(time(NULL));
    string playerR, playerL;
    cout << "Tooltip : \"RandAI\" jouera aléatoirement." << endl
         << "Entrez le nom des joueurs 1 et 2 :";
    cin >> playerR >> playerL;
    moves.setPlayers(playerR, playerL);
    moves.displayBoard();
    while(moves.continueGame()) {
        if(player1) {
            cout << "C'est au tour de " << playerR << ".\nEntrez la position de votre pion (colonne 'espace' ligne) : ";
            if(playerR == "RandAI") {
                do {
                    randX = rand() % moves.getLength();
                    randY = rand() % moves.getLength();
                } while(!moves.setPosition(randX, randY, 'x'));
            } else moves.nextMove('x');
            player1 = false;
        } else {
            cout << "C'est au tour de " << playerL << ".\nEntrez la position de votre pion (colonne 'espace' ligne) : ";
            if(playerL == "RandAI") {
                do {
                    randX = rand() % moves.getLength();
                    randY = rand() % moves.getLength();
                } while(!moves.setPosition(randX, randY, 'o'));
            } else moves.nextMove('o');
            player1 = true;
        }
        moves.displayBoard();
    }
    if (player1) {
        cout << endl << "Victoire du joueur " << playerL << "." << endl;
    } else {
        cout << endl << "Victoire du joueur " << playerR << "." << endl;
    }
}

int main() {
    newGame();

    return 0;
}
