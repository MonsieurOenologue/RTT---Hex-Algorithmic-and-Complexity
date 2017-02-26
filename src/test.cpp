#include <iostream>
#include <vector>
#include <string>
/**
 *  @file    AIManager.cpp
 *  @author  RTT
 *  @date    25/02/2017
 *  @version 1.0
 *
 *  @brief
 *
 *  @section DESCRIPTION
 *
 */
using namespace std;

int main()
{
    short plateau1[11][11] = {0};
    char plateau2[11][11] = {'\0'};
    string plateau3[11];
    vector<char> plateau4(11);
    vector<string> plateau5(11);

    for(int i = 0; i < plateau4.size(); ++i)
        plateau4[i] = '\0';

    for(int i = 0; i < plateau5.size(); ++i) {
        plateau5[i] = string(11, '0');
    }

    cout << "Sizeof(int) = " << sizeof(int) << endl
         << "Sizeof(bool) = " << sizeof(bool) << endl
         << "Sizeof(char) = " << sizeof(char) << endl
         << "Sizeof(short) = " << sizeof(short) << endl
         << "Sizeof(short[11][11]) = " << sizeof(plateau1) << endl
         << "Sizeof(char[11][11]) = " << sizeof(plateau2) << endl
         << "Sizeof(string[11]) = " << sizeof(plateau3) << endl
         << "Sizeof(vector<char>(11)) = " << sizeof(plateau4) << endl
         << "Sizeof(vector<string>(11)) = " << sizeof(plateau5) << endl << endl
         << "Affichage du plateau sous forme de vector<string>(11) :" << endl;

    for(int i = 0; i < plateau5.size(); ++i) {
        for(int j = 0; j < plateau5[i].size(); ++j)
            cout << plateau5[i][j] << " ";
        cout << endl;
    }

    return 0;
}
