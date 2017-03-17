#ifndef DATA_FILE_STORAGE_H
#define DATA_FILE_STORAGE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include "HexBoard.h"
#include "Action.h"


using namespace std;

class DataFileStorage {
private :
    fstream dataFile;
public :
            DataFileStorage();
            ~DataFileStorage();
    fstream& getDataFile();
    void    newDataFile();
    void    openDataFile();
    void    newDataFile(string);
    void    openDataFile(string);
    void    saveDataFile();
    void    saveDataFile(vector<char> movesTree, string, string);
    bool    loadGame();
    //In case we want to make a passage par référence with the file or something like that
    //DataFileStorage(const DataFileStorage&);
    //DataFileStorage& operator=(const DataFileStorage&);
};
#endif // DATA_FILE_STORAGE_H
