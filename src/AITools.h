#ifndef AITOOLS_H
#define AITOOLS_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class AITools {
private :


public :
            AITools();
            ~AITools();
    bool    learnMode();
    int     getHint();
    void    setDifficulty(int);
};

#endif // AITOOLS_H
