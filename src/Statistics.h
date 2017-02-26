#ifndef STATISTICS_H
#define STATISTICS_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include "Database.h"

using namespace std;

class Statistics {
private :
    Database instanceDatabase;
public :
            Statistics();
            ~Statistics();
    void    initStats();
    void    getStats();
    void    displayVictoryRatio();
};

#endif // STATISTICS_H
