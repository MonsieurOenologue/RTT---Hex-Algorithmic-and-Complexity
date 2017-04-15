#ifndef AITOOLS_H
#define AITOOLS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>

using namespace std;

typedef basic_string<unsigned char> ustring;

class AITools {
private :
    fstream dataFile;
public :
            AITools();
            ~AITools();
    bool    learnMode();
    void    getAndSaveCombinations(unsigned char, ustring, vector<ustring>);
    int     getHint();
    void    setDifficulty(int);
};

#endif // AITOOLS_H
