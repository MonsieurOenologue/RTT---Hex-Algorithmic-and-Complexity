#include "hexBoard.h"

void newGame() {
    hexBoard board;
    bool player1 = true;
    char x, y;
    string playerL, playerR;
    cout << "Entrez le nom des joueurs 1 et 2 :";
    cin >> playerL >> playerR;
    board.setPlayers(playerL, playerR);
    while(board.continueGame()) {
        board.displayBoard();
        if(player1) {
            cout << "C'est au tour de " << playerL << ".\nEntrez la position de votre pion (colonne 'espace' ligne) : ";
            cin >> y >> x;
            board.setPosition(x-97, y-65, 'x');
            player1 = false;
        } else {
            cout << "C'est au tour de " << playerR << ".\nEntrez la position de votre pion (colonne 'espace' ligne) : ";
            cin >> y >> x;
            board.setPosition(x-97, y-65, 'o');
            player1 = true;
        }
    }
}

int main() {
    newGame();

    return 0;
}
