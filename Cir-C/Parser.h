#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "MessageManager.h"
#include "Toolbox.h"
#include "LogicGate.h"

#include <iostream>
#include <string>
#include <list>
#include <map>

using namespace std;


bool parserInputTokenListDOT(list<Token>& listToken, map<string, LogicGateBase*>& outputGraph) {


	return false;
}


void convertJSONWaveToLogicState(const string& inputString, vector<LogicState>& outputVector) {
    // '=' not implemented

    for (int index = 0; index < inputString.length(); index++) {
        switch (inputString[index]) {
        case 'p': case 'P': case 'h': case 'H': case '1':
            outputVector.push_back(H);
            break;

        case 'n': case 'N': case 'l': case 'L': case '0':
            outputVector.push_back(L);
            break;

        case 'x':
            outputVector.push_back(X);
            break;

        case 'z':
            outputVector.push_back(Z);
            break;

        case '.': case '|':
            outputVector.push_back(outputVector.back());
            break;

        default:
            outputVector.push_back(X);
            break;            
        }
    }
}


bool parserJSONKeywordSignalGetNameWave(list<Token>& listToken, map<string, vector<LogicState>>& outputGraph) {
    auto itListToken = listToken.begin();
    bool endWhileFlag = false;
    list<Token> subListToken;
    int tempCounter = 0;
    string name = "";
    vector<LogicState> logicState;
    logicState.push_back(X);    

    while (itListToken != listToken.end() && !endWhileFlag) {
            if ((*itListToken).getType() == COMMENT) { itListToken++; continue; }
            if ((*itListToken).getType() != KEYWORD) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a KEYWORD"); return true; }
            
            if ((*itListToken).getValue() == "\"name\"" || (*itListToken).getValue() == "\'name\'" || (*itListToken).getValue() == "name") {
                
                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a COLON"); return true; }
                if ((*itListToken).getType() != COLON) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a COLON"); return true; }
                
                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a TEXT"); return true; }
                if ((*itListToken).getType() != TEXT) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a TEXT"); return true; }

                name = (*itListToken).getValue().substr(1, (*itListToken).getValue().length() - 2);
                
                itListToken++;
                if (itListToken != listToken.end()) {                    
                    if ((*itListToken).getType() != COMMA) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a COMMA"); return true; }
                    itListToken++;
                    if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "unexpected COMMA"); return true; }
                }
            }
            else if ((*itListToken).getValue() == "\"wave\"" || (*itListToken).getValue() == "\'wave\'" || (*itListToken).getValue() == "wave") {

                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a COLON"); return true; }
                if ((*itListToken).getType() != COLON) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a COLON"); return true; }
                
                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a TEXT"); return true; }
                if ((*itListToken).getType() != TEXT) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a TEXT"); return true; }

                convertJSONWaveToLogicState((*itListToken).getValue().substr(1, (*itListToken).getValue().length() - 2), logicState);
                
                itListToken++;
                if (itListToken != listToken.end()) {                    
                    if ((*itListToken).getType() != COMMA) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a COMMA"); return true; }
                    itListToken++;
                    if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "unexpected COMMA"); return true; }
                }  
            }
            else if ((*itListToken).getValue() == "\"data\"") {
                printWarningMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + (*itListToken).getTypeString() + " \"" + (*itListToken).getValue() + "\" not implemented");
            }
            else {
                printWarningMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "unexpected " + (*itListToken).getTypeString() + " \"" + (*itListToken).getValue() + "\"");
            }
        //itListToken++;
    }

    if (name != "" && logicState.size() != 1) {
        outputGraph.insert(pair<string, vector<LogicState>>(name, logicState));
        return false;
    }
    else return true;
    return true;
}

bool parserJSONKeywordSignal(list<Token>& listToken, map<string, vector<LogicState>>& outputGraph) {
    auto itListToken = listToken.begin();
    bool endWhileFlag = false;
    list<Token> subListToken;
    int tempCounter = 0;
        
    while (itListToken != listToken.end() && !endWhileFlag) {
        if ((*itListToken).getType() == COMMENT) { itListToken++; continue; }
        if ((*itListToken).getType() != LEFTCURLY) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "signal element need to start with a LEFTCURLY"); return true; }
        itListToken++;
        cleanListOfToken(subListToken);
            
        if (itListToken == listToken.end()) { return true; } // ---------------------------------------------------

        while (itListToken != listToken.end()) {
            if ((*itListToken).getType() == COMMENT) { itListToken++; continue; }
            if ((*itListToken).getType() == LEFTCURLY) tempCounter++;
            if ((*itListToken).getType() == RIGHTCURLY) {
                if (tempCounter == 0) break; else tempCounter--;
            }
            subListToken.push_back(*itListToken);
            itListToken++;
        }

        if (parserJSONKeywordSignalGetNameWave(subListToken, outputGraph)) return true;

        itListToken++;
        if (itListToken != listToken.end()) {                
            if ((*itListToken).getType() != COMMA) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a COMMA"); return true; }
            itListToken++;
            if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "unexpected COMMA"); return true; }
        }
        //itListToken++;
    }

    //RIGHTSQUARE

    return false;
}


bool parserInputTokenListJSON(list<Token>& listToken, map<string, vector<LogicState>>& outputGraph) {
    auto itListToken = listToken.begin();
    bool endWhileFlag = false;
    list<Token> subListToken;
    int tempCounter = 0;

    while((*itListToken).getType() == COMMENT) itListToken++;

    if (itListToken == listToken.end()) { return true; } // ------------------------------------------

    if ((*itListToken).getType() != LEFTCURLY) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "JSON file need to start with a LEFTCURLY"); return true; } 
    itListToken++;

    if (itListToken == listToken.end()) { return true; } // ----------------------------------------------

    while (itListToken != listToken.end() && !endWhileFlag) {
        if ((*itListToken).getType() == COMMENT) { itListToken++; continue; }

        if ((*itListToken).getType() != KEYWORD) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a KEYWORD"); return true; }
        
        if ((*itListToken).getValue() == "\"signal\"") {
            itListToken++;
            if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a COLON"); return true; }
            if ((*itListToken).getType() != COLON) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a COLON"); return true; }
            
            itListToken++;
            if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a LEFTSQUARE"); return true; }
            if ((*itListToken).getType() != LEFTSQUARE) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a LEFTSQUARE"); return true; }
            
            cleanListOfToken(subListToken);

            itListToken++;
            if (itListToken == listToken.end()) { return true; } // --------------------------------------  

            while (itListToken != listToken.end()) {
                if ((*itListToken).getType() == LEFTSQUARE) tempCounter++;
                if ((*itListToken).getType() == RIGHTSQUARE) {
                    if (tempCounter == 0) break; else tempCounter--;
                }
                subListToken.push_back(*itListToken);
                itListToken++;
            }
            if (parserJSONKeywordSignal(subListToken, outputGraph)) return true;
        }
        else if ((*itListToken).getValue() == "\"head\"") {
            printWarningMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + (*itListToken).getTypeString() + " \"" + (*itListToken).getValue() + "\" not implemented");
        }
        else if ((*itListToken).getValue() == "\"foot\"") {
            printWarningMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + (*itListToken).getTypeString() + " \"" + (*itListToken).getValue() + "\" not implemented");
        }
        else if ((*itListToken).getValue() == "\"config\"") {
            printWarningMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + (*itListToken).getTypeString() + " \"" + (*itListToken).getValue() + "\" not implemented");
        }
        else {
            printWarningMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "unexpected " + (*itListToken).getTypeString() + " \"" + (*itListToken).getValue() + "\"");
        }

        //RIGHTCURLY


        itListToken++;
        if (itListToken != listToken.end()) {                
            if ((*itListToken).getType() != COMMA) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "need a COMMA"); return true; }
            itListToken++;
            if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + +", " + "unexpected COMMA"); return true; }
        }
        //itListToken++;
    }
    
	return false;
}

#endif