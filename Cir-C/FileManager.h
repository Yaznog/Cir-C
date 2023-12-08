#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

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
    else cout << "Unable to open file";    
}

#endif