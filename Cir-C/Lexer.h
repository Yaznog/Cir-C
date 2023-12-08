#ifndef LEXER_H
#define LEXER_H

#include "Token.h"

#include <iostream>
#include <string>
#include <list>

using namespace std;

// identifier	| x, color, UP
// keyword		| if, while, return
// separator	| {, (, ;
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


int lexingInputStringJSON(const string& inputString, list<Token>& splittedElementTab) {
    string input = inputString;

    //addSpaceAroundSpecialChar(input);
    separateStringBySeparator(" ", input, splittedElementTab);


    return 0;
}


int lexingInputStringDOT(const string& inputString, const list<string>& splittedElementTab, const list<string>& tokenTab) {



	return 0;
}


#endif