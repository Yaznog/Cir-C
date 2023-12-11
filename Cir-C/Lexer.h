#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include "MessageManager.h"

#include <iostream>
#include <string>
#include <list>

using namespace std;

/*
void separateStringBySeparator(const string& separator, const string& inputString, list<Token>& splittedElementTab) {
    size_t pos;
    string input = inputString;
    string subInput = "";
        
    tokenType currentTokenType = UNKNOWN;
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
}*/


tokenType getStringTypeDOT(const string& inputString) {

    // box is also a keyword ???

    if (inputString.length() == 1) {
        switch (inputString[0]) {
        case '(':
            return LEFTPARENTHESIS;
        case ')': 
            return RIGHTPARENTHESIS;
        case '[': 
            return LEFTSQUARE;
        case ']': 
            return RIGHTSQUARE;
        case '{': 
            return LEFTCURLY;
        case '}': 
            return RIGHTCURLY;
        case ',': 
            return COMMA;
        case ';': 
            return SEMICOLON;
        case ':': 
            return COLON;
        case '=':
            return EQUAL;
        case '#':
            return HASH;
        default:
            return SYMBOLE;
        }
    }
    else if (inputString == "->")
        return AFFECTATION;
    else if (inputString == "//")
        return COMMENT;
    else if (inputString == "/*")
        return LEFTCOMMENT;
    else if (inputString == "*/")
        return RIGHTCOMMENT;
    else if ((inputString[0] == '\"' && inputString[inputString.length() - 1] == '\"') || (inputString[0] == '\'' && inputString[inputString.length() - 1] == '\'')) {
        if (inputString.substr(1, inputString.length()-2) == "digraph" || inputString.substr(1, inputString.length() - 2) == "label" || inputString.substr(1, inputString.length() - 2) == "shape" || inputString.substr(1, inputString.length() - 2) == "box")
            return KEYWORD;
        return TEXT;
    }
    else if (inputString == "digraph" || inputString == "label" || inputString == "shape" || inputString == "box")
        return KEYWORD;
    else 
        return SYMBOLE;
    return UNKNOWN;
}


tokenType getStringTypeJSON(const string& inputString) {

    if (inputString.length() == 1) {
        switch (inputString[0]) {
        case '(':
            return LEFTPARENTHESIS;
        case ')':
            return RIGHTPARENTHESIS;
        case '[':
            return LEFTSQUARE;
        case ']':
            return RIGHTSQUARE;
        case '{':
            return LEFTCURLY;
        case '}':
            return RIGHTCURLY;
        case ',':
            return COMMA;
        case ';':
            return SEMICOLON;
        case ':':
            return COLON;
        case '=':
            return EQUAL;
        case '#': // Forbidden in JSON files
            return HASH;
        default:
            return SYMBOLE;
        }
    }
    else if (inputString == "->")
        return AFFECTATION;
    else if (inputString == "//")
        return COMMENT;
    else if (inputString == "/*")
        return LEFTCOMMENT;
    else if (inputString == "*/")
        return RIGHTCOMMENT;
    else if ((inputString[0] == '\"' && inputString[inputString.length() - 1] == '\"') || (inputString[0] == '\'' && inputString[inputString.length() - 1] == '\'')) {
        if (inputString.substr(1, inputString.length() - 2) == "signal" || inputString.substr(1, inputString.length() - 2) == "name" || inputString.substr(1, inputString.length() - 2) == "wave" || inputString.substr(1, inputString.length() - 2) == "data")
            return KEYWORD;
        return TEXT;
    }
    else if (inputString == "signal" || inputString == "name" || inputString == "wave" || inputString == "data")
        return KEYWORD;
    else
        return SYMBOLE;
    return UNKNOWN;
}


void checkStringAndAddTokenInList(string& inputString, list<Token>& listToken, unsigned int lineNumber, const string& fileExtension) {
    if (inputString != "") {
        if (fileExtension == "JSON") {
            Token currentToken = Token(getStringTypeJSON(inputString), inputString, lineNumber);
            listToken.push_back(currentToken);
        }
        else if (fileExtension == "DOT") {
            Token currentToken = Token(getStringTypeDOT(inputString), inputString, lineNumber);
            listToken.push_back(currentToken);            
        }
        inputString = "";
    }
}


void splitString(const string& inputString, list<Token>& listToken, const string& fileExtension) {
    string currentString = "";
    unsigned int lineNumber = 1;

    for (int index = 0; index < inputString.length(); index++) {

        switch (inputString[index]) {
        case '\n':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            lineNumber++;
            break;

        case '(': case ')': case '[': case ']': case '{': case '}': case ',': case ';': case ':': case '=': case '#':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            currentString = inputString[index];
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            break;

        case '-':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            currentString = inputString[index];                
            if (index < inputString.length() - 1) {
                if (inputString[index + 1] == '>') {
                    currentString += inputString[index + 1];
                    checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
                    index++;
                }
                else
                    checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
                break;
            }
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            break;

        case '\"':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            currentString += inputString[index];                
            for (index = index + 1; index < inputString.length(); index++) {
                currentString += inputString[index];
                if (inputString[index] == '\"') {
                    break;
                }
            }
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            break;

        case '\'':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            currentString += inputString[index];
            for (index = index + 1; index < inputString.length(); index++) {
                currentString += inputString[index];
                if (inputString[index] == '\'') {
                    break;
                }
            }
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            break;

        case '/':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            currentString += inputString[index];
            if (index < inputString.length() - 1) {
                if (inputString[index + 1] == '/' || inputString[index + 1] == '*') {
                    currentString += inputString[index + 1];
                    checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
                    index++;
                }
                else
                    checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
                break;
            }
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            break;

        case '*':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            currentString += inputString[index];
            if (index < inputString.length() - 1) {
                if (inputString[index + 1] == '/') {
                    currentString += inputString[index + 1];
                    checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
                    index++;
                }
                else
                    checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
                break;
            }
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            break;

        case '\0': case ' ':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            break;

        default:
            currentString += inputString[index];
            break;
        }
    }
}


int lexingInputStringJSON(const string& inputString, list<Token>& listToken) {
    splitString(inputString, listToken, "JSON");

    return 0;
}


int lexingInputStringDOT(const string& inputString, list<Token>& listToken) {
    splitString(inputString, listToken, "DOT");

    return 0;
}

#endif