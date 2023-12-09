#ifndef LEXER_H
#define LEXER_H

#include "Token.h"

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

/*
list<int> c1, c2;
list<int>::const_iterator cIter;
c1.push_back(10);*/

/*
void addSpaceAroundSpecialChar(string& inputString) {

    for(int index = 0, )

}*/

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

/*
int lexingInputStringJSON(const string& inputString, list<string>& splittedElementTab, list<string>& tokenTab) {
    string input = inputString;

    //addSpaceAroundSpecialChar(input);
	separateStringBySeparator(" ", input, splittedElementTab, tokenTab);


	return 0;
}*/

string getStringType(const string& inputString) {

    return "NIY";
}


int lexingInputStringJSON(const string& inputString, list<Token>& listToken) {
    string currentString = "";
    //string workingString = inputString;
    Token currentToken;
    unsigned int lineNumber = 1;

    int previousIndex = 0;

    /*
    while (!workingString.empty()) {

        currentString = workingString.substr(0, index-1);
        workingString = workingString.substr(index + 1);
    }*/



    //for (int index = 0; index < inputString.length(); index++) {
    //bool breakWhile = false;
    bool breakFor = false;

    //while (!workingString.empty() && !breakWhile) {
        //breakFor = false;

        for (int index = 0; index < inputString.length(); index++) {
            //currentString = workingString.substr(0, index - 1);
            //workingString = workingString.substr(index + 1);

            switch (inputString[index])
            {
            case '\n':
                currentToken = Token(getStringType(currentString), currentString, lineNumber);
                listToken.push_back(currentToken);
                index++;
                                
                lineNumber++;
                currentString = "";
                break;

            case '{':
                currentToken = Token(getStringType(currentString), currentString, lineNumber);
                listToken.push_back(currentToken);

                currentString = inputString[index];
                currentToken = Token(getStringType(currentString), currentString, lineNumber);
                listToken.push_back(currentToken);

                currentString = "";
                break;

            case '}':
                currentToken = Token(getStringType(currentString), currentString, lineNumber);
                listToken.push_back(currentToken);

                currentString = inputString[index];
                currentToken = Token(getStringType(currentString), currentString, lineNumber);
                listToken.push_back(currentToken);

                currentString = "";
                break;

            case '[':
                currentToken = Token(getStringType(currentString), currentString, lineNumber);
                listToken.push_back(currentToken);

                currentString = inputString[index];
                currentToken = Token(getStringType(currentString), currentString, lineNumber);
                listToken.push_back(currentToken);

                currentString = "";
                break;

            case ']':
                currentToken = Token(getStringType(currentString), currentString, lineNumber);
                listToken.push_back(currentToken);

                currentString = inputString[index];
                currentToken = Token(getStringType(currentString), currentString, lineNumber);
                listToken.push_back(currentToken);

                currentString = "";
                break;

            case '(':
                currentToken = Token(getStringType(currentString), currentString, lineNumber);
                listToken.push_back(currentToken);

                currentString = inputString[index];
                currentToken = Token(getStringType(currentString), currentString, lineNumber);
                listToken.push_back(currentToken);

                currentString = "";
                break;

            case ')':
                currentToken = Token(getStringType(currentString), currentString, lineNumber);
                listToken.push_back(currentToken);

                currentString = inputString[index];
                currentToken = Token(getStringType(currentString), currentString, lineNumber);
                listToken.push_back(currentToken);

                currentString = "";
                break;
/*
            case '\0':
                //currentString = inputString.substr(previousIndex);
                //currentToken = Token(getStringType(currentString), currentString, lineNumber);
                //listToken.push_back(currentToken);
                //workingString = "";

                breakFor = true;
                //breakWhile = true;
                break;*/

            default:
                currentString += inputString[index];
                break;
            }

            if (breakFor)
                break;
        }
    //}

       


    //addSpaceAroundSpecialChar(input);
    //separateStringBySeparator(" ", input, splittedElementTab);

    return 0;
}


int lexingInputStringDOT(const string& inputString, const list<string>& splittedElementTab, const list<string>& tokenTab) {
       
	return 0;
}


#endif