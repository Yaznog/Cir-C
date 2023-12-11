#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "Token.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

using namespace std;

const string listOfArgsinputFilePathJSON[4] = { "-ij", "-IJ", "--inputjson", "--INPUTJSON" };
const string listOfArgsinputFilePathDOT[4] = { "-id", "-ID", "--inputdot", "--INPUTDOT" };
const string listOfArgsHelp[4] = { "-h", "-H", "--help", "--HELP" };

int inputArgumentParser(int argc, char* argv[], string& inputFilePathJSON, string& inputFilePathDOT) {

    //int rowsNb = sizeof(listOfInputArgs) / sizeof(listOfInputArgs[0]);
    //int colsNb = sizeof(listOfInputArgs[0]) / sizeof(listOfInputArgs[0][0]);

    for (int i = 1; i < argc; i++) {
        //cout << "i = " << i << "   " << argv[i] << endl;
        if (find(begin(listOfArgsinputFilePathJSON), end(listOfArgsinputFilePathJSON), argv[i]) != end(listOfArgsinputFilePathJSON)) {
            if (i + 1 != argc) {
                inputFilePathJSON = argv[i + 1];
                i++;
            }
            else
                cout << "ERROR: input JSON file path is missing after \"" << argv[i] << "\"" << endl;
        }

        else if (find(begin(listOfArgsinputFilePathDOT), end(listOfArgsinputFilePathDOT), argv[i]) != end(listOfArgsinputFilePathDOT)) {
            if (i + 1 != argc) {
                inputFilePathDOT = argv[i + 1];
                i++;
            }
            else
                cout << "ERROR: input JSON file path is missing after \"" << argv[i] << "\"" << endl;
        }

        else if (find(begin(listOfArgsHelp), end(listOfArgsHelp), argv[i]) != end(listOfArgsHelp)) {
            cout << "Args found" << endl;
        }

        else {
            cout << "Args not found: \"" << argv[i] << "\"" << endl;
        }

        //cout << find(begin(listOfArgsInputFile), end(listOfArgsInputFile), argv[i]) << endl;
    }
    cout << endl;

    return 0;
}


bool listsOfTokenAreEqual(list<Token>& list1, list<Token>& list2) {
    auto it1 = list1.begin();
    auto it2 = list2.begin();

    if(list1.size() != list2.size())
        return false;

    while (it1 != list1.end() && it2 != list2.end())
    {
        if (*it1 != *it2)
            return false;
        it1++;
        it2++;
    }
    return true;
}

#endif