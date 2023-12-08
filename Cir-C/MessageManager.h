#ifndef MESSAGE_MANAGER_H
#define MESSAGE_MANAGER_H

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <list>

#include "Token.h"

using namespace std;

void printInConsoleStartUpMessage() {
    time_t startTime = chrono::system_clock::to_time_t(chrono::system_clock::now());

    string msg = "";
    msg += "################################################################################\n";
    msg += "Welcome to Cir-C simulator !!!\n";
    msg += ctime(&startTime);

    cout << msg << endl;
}


void printInConsoleStopDownpMessage() {
    string msg = "";
    msg += "\n";
    msg += "Bye !!!\n";
    msg += "################################################################################";

    cout << msg << endl;
}


void printInConsoleFileDOT(const string& inputString) {
    string msg = "";
    cout << "\nPrint DOT file:\n" << endl;
    cout << inputString << endl;

    cout << msg << endl;
}


void printInConsoleFileJSON(const string& inputString) {
    string msg = "";
    cout << "\nPrint JSON file:\n" << endl;
    cout << inputString << endl;

    cout << msg << endl;
}


void printInConsoleListString(const string& startMessage, const list<string>& inputStringList) {
    string msg = startMessage + "\n";
    for (auto listElement : inputStringList)
        msg += listElement + "\n";

    cout << msg << endl;
}


void printInConsoleListToken(const string& startMessage, const list<Token>& inputListToken) {
    string msg = startMessage + "\n";
    for (auto listElement : inputListToken)
        msg += listElement.toString() + "\n";

    cout << msg << endl;
}

#endif