#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "MessageManager.h"

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

void extractFile(const string& inputFilePath, string& outputString) {    
    string line;
    ifstream myfile(inputFilePath);
    if (myfile.is_open())
    {
        while (getline(myfile, line)) outputString += line + "\n";
        myfile.close();
    }
    else printErrorMessage("Unable to open file");    
}

void createFile(const string& inputFilePath, const string& inputString) {
    ofstream MyFile(inputFilePath);
    MyFile << inputString;
    MyFile.close();
}

#endif