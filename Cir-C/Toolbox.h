#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "Token.h"
//#include "LogicGate.h"
//#include "Parser.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const string listOfArgsInputFilePathJSON[4] =   { "-j", "-J", "--inputjson",    "--INPUTJSON" };
const string listOfArgsInputFilePathDOT[4] =    { "-d", "-D", "--inputdot",     "--INPUTDOT" };
const string listOfArgsOutputFilePathJSON[4] =  { "-o", "-O", "--outputjson",   "--OUTPUTJSON" };
//const string listOfArgsPrint[4] =               { "-p", "-P", "--print",        "--PRINT" };
const string listOfArgsHelp[4] =                { "-h", "-H", "--help",         "--HELP" };

int inputArgumentParser(int argc, char* argv[], string& inputFilePathJSON, string& inputFilePathDOT, string& outputFilePathJSON) {

    //int rowsNb = sizeof(listOfInputArgs) / sizeof(listOfInputArgs[0]);
    //int colsNb = sizeof(listOfInputArgs[0]) / sizeof(listOfInputArgs[0][0]);

    for (int i = 1; i < argc; i++) {
        //cout << "i = " << i << "   " << argv[i] << endl;
        if (find(begin(listOfArgsInputFilePathJSON), end(listOfArgsInputFilePathJSON), argv[i]) != end(listOfArgsInputFilePathJSON)) {
            if (i + 1 != argc) {
                inputFilePathJSON = argv[i + 1];
                i++;
            }
            else
                cout << "ERROR: input JSON file path is missing after \"" << argv[i] << "\"" << endl;
        }

        else if (find(begin(listOfArgsInputFilePathDOT), end(listOfArgsInputFilePathDOT), argv[i]) != end(listOfArgsInputFilePathDOT)) {
            if (i + 1 != argc) {
                inputFilePathDOT = argv[i + 1];
                i++;
            }
            else
                cout << "ERROR: input JSON file path is missing after \"" << argv[i] << "\"" << endl;
        }

        else if (find(begin(listOfArgsOutputFilePathJSON), end(listOfArgsOutputFilePathJSON), argv[i]) != end(listOfArgsOutputFilePathJSON)) {
            if (i + 1 != argc) {
                outputFilePathJSON = argv[i + 1];
                i++;
            }
            else
                cout << "ERROR: output JSON file path is missing after \"" << argv[i] << "\"" << endl;
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


int listsOfTokenAreEqual(list<Token>& list1, list<Token>& list2) {
    auto it1 = list1.begin();
    auto it2 = list2.begin();

    if(list1.size() != list2.size())
        return -1;

    while (it1 != list1.end() && it2 != list2.end())
    {
        if (*it1 != *it2)
            //return false;
            return (*it1).getLine();
        it1++;
        it2++;
    }
    return 0;
}


int stringsAreEqual(const string& inputString1, const string& inputString2) {
    if (inputString1.size() != inputString1.size())
        return -1;

    int lineNb = 1;

    for (int i = 0; i < inputString1.size(); i++) {
        if (inputString1[i] == '\n') lineNb++;
        if (inputString1[i] != inputString2[i]) return lineNb;
    }
    return 0;
}


void cleanListOfToken(list<Token>& inputList) {
    inputList.erase(inputList.begin(), inputList.end());
}


inline unsigned int max(unsigned int inputValueA, unsigned int inputValueB) { return (inputValueA >= inputValueB) ? inputValueA : inputValueB; }
inline int          max(int inputValueA, int inputValueB)                   { return (inputValueA >= inputValueB) ? inputValueA : inputValueB; }




#endif