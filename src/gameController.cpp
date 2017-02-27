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
    char x, y;
    string playerL, playerR;
    cout << "Entrez le nom des joueurs 1 et 2 :";
    cin >> playerL >> playerR;
    moves.setPlayers(playerL, playerR);
    while(moves.continueGame()) {
        moves.displayBoard();
        if(player1) {
            cout << "C'est au tour de " << playerL << ".\nEntrez la position de votre pion (colonne 'espace' ligne) : ";
            do {
                cin >> y >> x;
            } while(y < 65 || x < 97 || y > 64 + moves.getLength() || x > 96 + moves.getLength());
            moves.nextMove(x-97, y-65, 'x');
            player1 = false;
        } else {
            cout << "C'est au tour de " << playerR << ".\nEntrez la position de votre pion (colonne 'espace' ligne) : ";
            do {
                cin >> y >> x;
            } while(y < 65 || x < 97 || y > 64 + moves.getLength() || x > 96 + moves.getLength());
            moves.nextMove(x-97, y-65, 'o');
            player1 = true;
        }
    }
}

int main() {
    newGame();

    return 0;
}
