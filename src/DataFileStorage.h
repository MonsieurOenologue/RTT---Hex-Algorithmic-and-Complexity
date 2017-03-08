#ifndef DATA_FILE_STORAGE_H
#define DATA_FILE_STORAGE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>


using namespace std;

class DataFileStorage {
private :
    fstream dataFile;
public :
            DataFileStorage();
            ~DataFileStorage();
    fstream& getDataFile();
    void    newFile();
    void    openFile();
    void    saveFile();
    void    loadGame();
    //In case we want to make a passage par référence with the file or something like that
    //DataFileStorage(const DataFileStorage&);
    //DataFileStorage& operator=(const DataFileStorage&);
};
#endif // DATA_FILE_STORAGE_H
