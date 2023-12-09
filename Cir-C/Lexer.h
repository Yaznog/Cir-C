#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include "MessageManager.h"

#include <iostream>
#include <string>
#include <list>

using namespace std;

// symbole	    | x, color, UP
// keyword		| if, while, return
// separator	| {, [, (, ;
// operator		| +, =, <
// literal      | true, 0.15, "music"
// comment      | //comment


void separateStringBySeparator(const string& separator, const string& inputString, list<Token>& splittedElementTab) {
    size_t pos;
    string input = inputString;
    string subInput = "";
        
    string currentTokenType = "";
    string currentTokenValue = "";
    int currentTokenLine = -1;
    Token currentToken(currentTokenType, currentTokenValue, currentTokenLine);

    while (!input.empty()) {
        pos = input.find(separator);

        if (pos == string::npos) {
            subInput = input;
            break;
        }
        subInput = input.substr(0, pos);
        input = input.substr(pos + 1);

        currentTokenType = Token::getStringType(subInput);

        currentToken.setType(currentTokenType);
        currentToken.setValue(currentTokenValue);
        currentToken.setLine(currentTokenLine);

        splittedElementTab.push_back(currentToken);
    }
}


string getStringType(const string& inputString) {

    return "NIY";
}


/*
void cleanSplitString(string& inputString) {
    int startIndex;
    int endIndex;

    for (startIndex = 0; startIndex < inputString.length(); startIndex++) {
        if (inputString[startIndex] != ' ')
            break;
    }
    for (endIndex = inputString.length() - 1; endIndex > 0; endIndex--) {
        if (inputString[endIndex] != ' ')
            break;
    }
    inputString = inputString.substr(startIndex, endIndex - startIndex + 1);
}*/


void checkStringAndAddTokenInList(string& inputString, list<Token>& listToken, unsigned int lineNumber) {
    if (inputString != "") {
        Token currentToken = Token(getStringType(inputString), inputString, lineNumber);
        listToken.push_back(currentToken);
        inputString = "";
    }
}


void splitString(const string& inputString, list<Token>& listToken) {

    string currentString = "";
    unsigned int lineNumber = 1;

    for (int index = 0; index < inputString.length(); index++) {

        switch (inputString[index])
        {
        case '\n':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber);
            lineNumber++;
            break;

        case '(': case ')': case '[': case ']': case '{': case '}': case ',': case ';': case ':': case '=':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber);
            currentString = inputString[index];
            checkStringAndAddTokenInList(currentString, listToken, lineNumber);
            break;

        case '-':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber);
            currentString = inputString[index];                
            if (index < inputString.length() - 1) {
                if (inputString[index + 1] == '>') {
                    currentString += inputString[index + 1];
                    checkStringAndAddTokenInList(currentString, listToken, lineNumber);
                    index++;
                }
                else
                    checkStringAndAddTokenInList(currentString, listToken, lineNumber);
                break;
            }
            checkStringAndAddTokenInList(currentString, listToken, lineNumber);
            break;

        case '\"':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber);
            currentString += inputString[index];                
            for (index = index + 1; index < inputString.length(); index++) {
                currentString += inputString[index];
                if (inputString[index] == '\"') {
                    break;
                }
            }
            checkStringAndAddTokenInList(currentString, listToken, lineNumber);
            break;

        case '\0': case ' ':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber);
            break;

        default:
            currentString += inputString[index];
            break;
        }
    }
}


int lexingInputStringJSON(const string& inputString, list<Token>& listToken) {
    list<string> splitStringList;
    list<unsigned int> splitStringLineList;
    splitString(inputString, listToken);

    return 0;
}


int lexingInputStringDOT(const string& inputString, list<Token>& listToken) {
    list<string> splitStringList;
    list<unsigned int> splitStringLineList;
    splitString(inputString, listToken);

    return 0;
}

#endif