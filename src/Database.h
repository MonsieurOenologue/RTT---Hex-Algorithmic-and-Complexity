#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class Database {
private :


public :
            Database();
            ~Database();
    void    newDatabase();
    bool    openDatabase();
    bool    saveDatabase();
    bool    loadGame();
};

#endif // DATABASE_H
