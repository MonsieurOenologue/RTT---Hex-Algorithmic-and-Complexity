#include "AITools.h"
/**
 *  \file    AITools.cpp
 *  \author  RTT
 *  \date    25/02/2017
 *  \version 1.0
 *
 *  \brief Contains some necessary tools for our "AI" algorithms.
 *
 *
 */
AITools::AITools() {}

AITools::~AITools() {}


bool fileExists(const std::string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

void AITools::getAndSaveCombinations(unsigned char move, ustring aSolution, vector<ustring> allSolutions) {
    ifstream dataFileIn;
    ofstream dataFileOut;

    unsigned char aSolutionString;
    aSolutionString = (unsigned char)'a';
    aSolution = ustring(1, aSolutionString);
    aSolutionString = *aSolution.c_str();

    cout << "debug - test de l'appel de fonction" << endl;

    //Creating a new file
    if(!fileExists("player1Moves.txt") && !fileExists("player2moves.txt")){
        dataFileOut.open("player1Moves.txt", fstream::out);
        dataFileOut.open("player2Moves.txt", fstream::out);
        dataFileOut.close();
        dataFileOut << "Creation of files succesful !" << endl;
    }

    else{
    dataFileOut.open("player1Moves.txt", fstream::in |  fstream::out | fstream::app);
    dataFileOut.open("player2Moves.txt", fstream::in |  fstream::out | fstream::app);
        if (dataFileOut.is_open()){
        cout << "File has been opened properly";

        //Browse the tree and display the solutions for each turn played
        dataFileOut << move;
        dataFileOut << aSolutionString;

        vector<char> a(allSolutions.begin(), allSolutions.end());

        for (vector<char>::const_iterator i = a.begin(); i != a.end(); ++i) {
            dataFileOut << *i << ", "; //invalid operands to binary expression
            //dataFileOut << "le test de bucheron" << endl;
        }

        dataFileOut << "\n";
        }
        else {
            cout << "Failed to open the file :(" << endl;
        }
    }
    dataFileOut.close();
}
