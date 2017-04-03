#include "Bruteforce.h"
#include "Action.h"
#include "HexBoard.h"
/**
 *  @file    Bruteforce.cpp
 *  @author  RTT
 *  @date    25/02/2017
 *  @version 1.0
 *
 *  @brief
 *
 *  @section DESCRIPTION
 *
 */
bool Bruteforce::Bruteforce() {
    vector<string> TMP = HexBoard.board;
    if(player == playerL) {
        for(char i = 0; i < HexBoard.nbPawnsPlayed; i++) {
            for(char j = 0; j < HexBoard.nbPawnsPlayed - i; j++){
                for(char x = 0; x < HexBoard.length; x++) {
                    for(char y = 0; y < HexBoard.length; y++) {
                        if(TMP[x][y] == ' ') {
                            if(!HexBoard.victoryByRecursion(x,y)) {
                            TMP[x][y] = x;
                            }
                        else setPosition(x,y,'x');
                        }

                    }
                }
            }
        }
    }
    else {for(char i = 0; i < HexBoard.nbPawnsPlayed; i++) {
            for(char j = 0; j < HexBoard.nbPawnsPlayed - i; j++){
                for(char x = 0; x < HexBoard.length; x++) {
                    for(char y = 0; y < HexBoard.length; y++) {
                        if(TMP[x][y] == ' ') {
                            if(!HexBoard.victoryByRecursion(x,y)) {
                            TMP[x][y] = x;
                            }
                        else setPosition(x,y,'o');
                        }

                    }
                }
            }
        }
    }

    }
}

Bruteforce::~Bruteforce() {}
