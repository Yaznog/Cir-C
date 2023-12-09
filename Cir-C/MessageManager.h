#ifndef MESSAGE_MANAGER_H
#define MESSAGE_MANAGER_H

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <list>
#include <iomanip>

#include "Token.h"

#define RESET       "\033[0m"
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define BOLD        "\033[1m"
#define UNDERLINE   "\033[4m"

using namespace std;

void printInConsoleStartUpMessage() {
    time_t startTime = chrono::system_clock::to_time_t(chrono::system_clock::now());

    cout << BOLD << "################################################################################" << RESET << endl;
    cout << BOLD << "Welcome to Cir-C simulator !!!" << RESET << endl;
    cout << BOLD << ctime(&startTime) << RESET << endl;
}


void printInConsoleStopDownpMessage() {
    cout << endl;
    cout << BOLD << GREEN << "DONE" << RESET << endl;
    cout << BOLD << "################################################################################" << RESET << endl;
}


void printInConsoleFileDOT(const string& inputString) {
    cout << "\nPrint DOT file:\n" << endl;
    cout << inputString << endl;
}


void printInConsoleFileJSON(const string& inputString) {
    cout << BOLD << "\nPrint JSON file:\n" << RESET << endl;
    cout << inputString << endl;
}


void printInConsoleListString(const string& startMessage, const list<string>& inputStringList) {
    cout << startMessage << endl;
    for (auto listElement : inputStringList)
        cout << listElement << endl;
}


void printInConsoleListToken(const string& startMessage, const list<Token>& inputListToken) {
    cout << startMessage << endl;
    for (auto listElement : inputListToken)
        //cout << listElement.toString() << endl;
        cout << left << "Value: \"" << setw(75) << (listElement.getValue() + "\"") << left << "Type: " << setw(10) << listElement.getType() << left << "Line: " << setw(5) << to_string(listElement.getLine()) << endl << "--------------------------------------------------" << endl;
}

inline void printErrorMessage(const string& inputString)    { cout << BOLD << RED       << "Error: "    << RESET << inputString << endl; }
inline void printWarningMessage(const string& inputString)  { cout << BOLD << MAGENTA   << "Warning: "  << RESET << inputString << endl; }
inline void printInfoMessage(const string& inputString)     { cout << BOLD << BLUE      << "Info: "     << RESET << inputString << endl; }
inline void printDevMessage(const string& inputString)      { cout << BOLD << CYAN      << "Dev: "      << RESET << inputString << endl; }

#endif