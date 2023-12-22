#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include "MessageManager.h"
#include "Toolbox.h"

#include <iostream>
#include <string>
#include <list>

using namespace std;


TokenType getStringTypeDOT(const string& inputString) {

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
        case '/':
            return SLASH;
        default:
            return SYMBOLE;
        }
    }
    else if (inputString == "->")
        return AFFECTATION;
    else if (inputString[0] == '#' || (inputString[0] == '/' && inputString[1] == '/') || (inputString[0] == '/' && inputString[1] == '*' ))
        return COMMENT;
    //else if (inputString == "//")
    //    return COMMENT;
    else if (inputString == "/*")
        return LEFTCOMMENT;
    else if (inputString == "*/")
        return RIGHTCOMMENT;
    else if ((inputString[0] == '\"' && inputString[inputString.length() - 1] == '\"') || (inputString[0] == '\'' && inputString[inputString.length() - 1] == '\'')) {
        if (find(keywordArrayDOT, keywordArrayDOT + sizeof(keywordArrayDOT) / sizeof(int), inputString.substr(1, inputString.length() - 2)) != (keywordArrayDOT + sizeof(keywordArrayDOT) / sizeof(int)))
            return KEYWORD;
        return TEXT;
    }
    else if (find(keywordArrayDOT, keywordArrayDOT + sizeof(keywordArrayDOT) / sizeof(int), inputString) != (keywordArrayDOT + sizeof(keywordArrayDOT) / sizeof(int)))
        return KEYWORD;
    else 
        return SYMBOLE;
    return UNKNOWN;
}


TokenType getStringTypeJSON(const string& inputString) {

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
        case '/':
            return SLASH;
        default:
            return SYMBOLE;
        }
    }
    else if (inputString == "->")
        return AFFECTATION;
    //else if (inputString[0] == '/' && inputString[1] == '/')
    //    return COMMENT;
    else if (inputString[0] == '#' || (inputString[0] == '/' && inputString[1] == '/') || (inputString[0] == '/' && inputString[1] == '*'))
        return COMMENT;
    else if (inputString == "/*")
        return LEFTCOMMENT;
    else if (inputString == "*/")
        return RIGHTCOMMENT;    
    else if ((inputString[0] == '\"' && inputString[inputString.length() - 1] == '\"') || (inputString[0] == '\'' && inputString[inputString.length() - 1] == '\'')) {
        if (find(keywordArrayJSON, keywordArrayJSON + sizeof(keywordArrayJSON) / sizeof(int), inputString.substr(1, inputString.length() - 2)) != (keywordArrayJSON + sizeof(keywordArrayJSON) / sizeof(int)))
            return KEYWORD;
        return TEXT;
    }
    else if (find(keywordArrayJSON, keywordArrayJSON + sizeof(keywordArrayJSON) / sizeof(int), inputString) != (keywordArrayJSON + sizeof(keywordArrayJSON) / sizeof(int)))
        return KEYWORD;
    /*
    else if (inputString == "signal" || inputString == "name" || inputString == "wave" || inputString == "data")
        return KEYWORD;*/
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

        case '(': case ')': case '[': case ']': case '{': case '}': case ',': case ';': case ':': case '=':
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            currentString = inputString[index];
            checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
            break;

        case '#':
            if (fileExtension == "DOT") {
                checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
                currentString += inputString[index];
                //index++;
                for (index = index + 1; index < inputString.length() - 1; index++) {
                    currentString += inputString[index];
                    if (inputString[index + 1] == '\n')
                        break;
                }
            }
            else {
                checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
                currentString = inputString[index];
                checkStringAndAddTokenInList(currentString, listToken, lineNumber, fileExtension);
                break;
            }  
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
            if (index + 1 < inputString.length()) {
                if (inputString[index + 1] == '/') {
                    currentString += inputString[index + 1];
                    index++;
                    for (index = index + 1; index < inputString.length()-1; index++) {
                        currentString += inputString[index];
                        if (inputString[index+1] == '\n')
                            break;                            
                    }
                }
                else if (inputString[index + 1] == '*') {
                    currentString += inputString[index + 1];
                    index++;
                    /*
                    if (inputString[index + 1] == '\0') {
                        if (inputString[index + 1] == '\n')
                            lineNumber++;
                    }*/

                    for (index = index + 1; index < inputString.length() - 2; index++) {
                        currentString += inputString[index];
                        //if (inputString[index + 1] == '\n')
                            //lineNumber++;
                        if (inputString[index + 1] == '*' && inputString[index + 2] == '/') {
                            currentString += inputString[index + 1];
                            index++;
                            currentString += inputString[index + 1];
                            //index++;
                            break;
                        }
                    }
                    for (auto currentChar : currentString) {
                        if (currentChar == '\n') lineNumber++;
                    }

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