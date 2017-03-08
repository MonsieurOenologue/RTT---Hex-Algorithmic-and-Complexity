#include "DataFileStorage.h"
/**
 *  @file    DataFileStorage.cpp
 *  @author  RTT
 *  @date    7/03/2017
 *  @version 1.0
 *
 *  @brief
 *
 *  @section DESCRIPTION
 *
 */
DataFileStorage::DataFileStorage() {
}

DataFileStorage::~DataFileStorage() {
}

void newDataFile() {
    ofstream dataFileOut;
    dataFileOut.open("DataFromPlays.csv");
}

void newDataFile(string name) {
    ofstream dataFileOut;
    dataFileOut.open(name);
}

void openDataFile() {
    ifstream dataFileIn;
    dataFileIn.open("DataFromPlays.csv");
}

void openDataFile(string name) {
    ifstream dataFileIn;
    dataFileIn.open(name);
}

void saveDataFile(vector<char> movesTree) {
    ofstream dataFileOut;
    dataFileOut.open("DataFromPlays.csv");

    cout << string(begin(movesTree), end(movesTree)) << endl;
    dataFileOut.close();
}

bool loadGame() {
    return true;
}
