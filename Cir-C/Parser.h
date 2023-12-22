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

const int nbTypes = 10;
const unsigned int maxStringLength = 30;

enum class GateType {
    INPUT,
    OUTPUT,
    AND,
    OR,
    XOR,
    NOT,
    REGISTER,
    NOTYPE
};

    /// -------------------------------------------------------------------------------------------
    /// PARSER JSON 
    /// -------------------------------------------------------------------------------------------


void convertJSONWaveToLogicState(const string& inputString, vector<LogicState>& outputVector) {

    for (int index = 0; index < inputString.length(); index++) {
        switch (inputString[index]) {
        case 'p': case 'P': case 'h': case 'H': case '1':
            outputVector.push_back(LogicState::H);
            break;

        case 'n': case 'N': case 'l': case 'L': case '0':
            outputVector.push_back(LogicState::L);
            break;

        case 'x':
            outputVector.push_back(LogicState::X);
            break;

        case 'z':
            outputVector.push_back(LogicState::Z);
            break;

        case '.': case '|':
            outputVector.push_back(outputVector.back());
            break;

        default:
            outputVector.push_back(LogicState::X);
            break;            
        }
    }
}


string convertLogicStateWaveToString(vector<LogicState>& inputVector) {
    string outputString = "";
    char tempChar = ' ';
    char previousChar;
    for (int index = 0; index < inputVector.size(); index++) {
                        
        switch (inputVector[index]) {
        case LogicState::H:
            tempChar = '1';
            break;

        case LogicState::L:
            tempChar = '0';
            break;

        case LogicState::X:
            tempChar = 'x';
            break;

        case LogicState::Z:
            tempChar = 'z';
            break;
        }
        if (index != 0) {
            if (previousChar == tempChar)
                outputString += ".";
            else
                outputString += tempChar;
        }
        previousChar = tempChar;
    }
    return outputString;
}


void convertJSONWaveToString(map<string, vector<LogicState>> outputGraphJSON, map<string, vector<LogicState>> inputGraphJSON, string& outputString) {
    outputString += "{\n  \"signal\": [\n";
    for (auto listElement : inputGraphJSON)
        outputString += ("    {name: \'" + listElement.first + "\', wave: \'" + convertLogicStateWaveToString((listElement.second)) + "\'},\n");
    for (auto listElement : outputGraphJSON)
        outputString += ("    {name: \'" + listElement.first + "\', wave: \'" + convertLogicStateWaveToString((listElement.second)) + "\'},\n");
    outputString += "]\n}\n";
}//vectorLogicStateToString


bool parserJSONKeywordSignalGetNameWave(list<Token>& listToken, map<string, vector<LogicState>>& outputGraph) {
    auto itListToken = listToken.begin();
    bool endWhileFlag = false;
    list<Token> subListToken;
    int tempCounter = 0;
    string name = "";
    vector<LogicState> logicState;
    logicState.push_back(LogicState::X);

    while (itListToken != listToken.end() && !endWhileFlag) {
            if ((*itListToken).getType() == COMMENT) { itListToken++; continue; }
            if ((*itListToken).getType() != KEYWORD) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a KEYWORD"); return true; }
            
            if ((*itListToken).getValue() == "\"name\"" || (*itListToken).getValue() == "\'name\'" || (*itListToken).getValue() == "name") {
                
                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a COLON"); return true; }
                if ((*itListToken).getType() != COLON) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a COLON"); return true; }
                
                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a TEXT"); return true; }
                if ((*itListToken).getType() != TEXT) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a TEXT"); return true; }

                name = (*itListToken).getValue().substr(1, (*itListToken).getValue().length() - 2);
                
                itListToken++;
                if (itListToken != listToken.end()) {                    
                    if ((*itListToken).getType() != COMMA) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a COMMA"); return true; }
                    itListToken++;
                    if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "unexpected COMMA"); return true; }
                }
            }
            else if ((*itListToken).getValue() == "\"wave\"" || (*itListToken).getValue() == "\'wave\'" || (*itListToken).getValue() == "wave") {

                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a COLON"); return true; }
                if ((*itListToken).getType() != COLON) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a COLON"); return true; }
                
                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a TEXT"); return true; }
                if ((*itListToken).getType() != TEXT) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a TEXT"); return true; }

                convertJSONWaveToLogicState((*itListToken).getValue().substr(1, (*itListToken).getValue().length() - 2), logicState);
                
                itListToken++;
                if (itListToken != listToken.end()) {                    
                    if ((*itListToken).getType() != COMMA) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a COMMA"); return true; }
                    itListToken++;
                    if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "unexpected COMMA"); return true; }
                }  
            }
            else if ((*itListToken).getValue() == "\"data\"") {
                printWarningMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + (*itListToken).getTypeString() + " \"" + (*itListToken).getValue() + "\" not implemented");
                do {
                    itListToken++;
                    if (itListToken == listToken.end()) break;
                    if ((*itListToken).getType() == KEYWORD) break;                    
                } while (itListToken != listToken.end());

            }
            else {
                printWarningMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "unexpected " + (*itListToken).getTypeString() + " \"" + (*itListToken).getValue() + "\"");
                do {
                    itListToken++;
                    if (itListToken == listToken.end()) break;
                    if ((*itListToken).getType() == KEYWORD) break;
                } while (itListToken != listToken.end());
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

    //printInConsoleListToken("listToken: ", listToken);
        
    while (itListToken != listToken.end() && !endWhileFlag) {
        if ((*itListToken).getType() == COMMENT) { itListToken++; continue; }
        if ((*itListToken).getType() != LEFTCURLY) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "signal element need to start with a LEFTCURLY"); return true; }
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
            if ((*itListToken).getType() != COMMA) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a COMMA"); return true; }
            itListToken++;
            //if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "unexpected COMMA"); return true; }
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

    //printInConsoleListToken("listToken: ", listToken);

    while((*itListToken).getType() == COMMENT) itListToken++;

    if (itListToken == listToken.end()) { return true; } // ------------------------------------------

    if ((*itListToken).getType() != LEFTCURLY) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "JSON file need to start with a LEFTCURLY"); return true; } 
    itListToken++;

    if (itListToken == listToken.end()) { return true; } // ----------------------------------------------

    while (itListToken != listToken.end() && !endWhileFlag) {
        if ((*itListToken).getType() == COMMENT) { itListToken++; continue; }

        if ((*itListToken).getType() != KEYWORD) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a KEYWORD"); return true; }
        
        if ((*itListToken).getValue() == "\"signal\"" || (*itListToken).getValue() == "\'signal\'" || (*itListToken).getValue() == "signal") {
            itListToken++;
            if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a COLON"); return true; }
            if ((*itListToken).getType() != COLON) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a COLON"); return true; }
            
            itListToken++;
            if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a LEFTSQUARE"); return true; }
            if ((*itListToken).getType() != LEFTSQUARE) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a LEFTSQUARE"); return true; }
            
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
            printWarningMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + (*itListToken).getTypeString() + " \"" + (*itListToken).getValue() + "\" not implemented");
        }
        else if ((*itListToken).getValue() == "\"foot\"") {
            printWarningMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + (*itListToken).getTypeString() + " \"" + (*itListToken).getValue() + "\" not implemented");
        }
        else if ((*itListToken).getValue() == "\"config\"") {
            printWarningMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + (*itListToken).getTypeString() + " \"" + (*itListToken).getValue() + "\" not implemented");
        }
        else {
            printWarningMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "unexpected " + (*itListToken).getTypeString() + " \"" + (*itListToken).getValue() + "\"");
        }

        //RIGHTCURLY
        

        itListToken++;
        if (itListToken != listToken.end()) {       
            if ((*itListToken).getType() != RIGHTCURLY) {
                if ((*itListToken).getType() != COMMA) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a COMMA"); return true; }
                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "unexpected COMMA"); return true; }
            }
            else if ((itListToken++) == listToken.end())
                return false;
        }
        //itListToken++;
    }
    
	return false;
}


    /// -------------------------------------------------------------------------------------------
    /// PARSER DOT 
    /// -------------------------------------------------------------------------------------------


GateType ConvertStringToGateType(string type) {
    if (type == "\"INPUT\"") return GateType::INPUT;
    if (type == "\"OUTPUT\"") return GateType::OUTPUT;
    if (type.substr(0, 4) == "\"AND") return GateType::AND;
    if (type.substr(0, 3) == "\"OR") return GateType::OR;
    if (type.substr(0, 4) == "\"XOR") return GateType::XOR;
    if (type.substr(0, 4) == "\"NOT") return GateType::NOT;
    if (type == "\"FF\"") return GateType::REGISTER;
    return GateType::NOTYPE;
};


bool parserInputTokenListDOT(list<Token>& listToken, map<string, LogicGateBase*>& outputGraphDOT, string& circuitName) {
    auto itListToken = listToken.begin();
    auto tempItListToken = itListToken;
    vector<string> tempVector;
    //string circuitName = "";
    string currentName = "";
    GateType currentType = GateType::NOTYPE;
    map<string, LogicGateBase*>::iterator itGraphDOT;

    if (listToken.size() == 0) { printErrorMessage("Input list of token is empty"); return true; }

        /// Tant que c'est un commentaire, on passe au token suivant
    while ((*itListToken).getType() == COMMENT) itListToken++;
    if (itListToken == listToken.end()) { return true; }

        /// Si on n'a pas "digraph" pour commencer -> erreur
    if ((*itListToken).getValue() != "digraph") { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", DOT file must start with digraph"); return true; }
    itListToken++;

        /// Si le digraph a un nom, on l'enregistre puis on passe à la suite
    if ((*itListToken).getType() == SYMBOLE) {
        if ((*itListToken).getValue().length() >= maxStringLength) { printWarningMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", digraph name too long"); return true; }
        circuitName = (*itListToken).getValue();
        itListToken++;
    }

        /// S'il n'y a pas de { -> erreur
    if ((*itListToken).getType() != LEFTCURLY) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a LEFTCURLY"); return true; }
    itListToken++;
        
    // --------------------------------------------------------------------------------------------

        /// Boucle de lecture des entrées sorties
    while (itListToken != listToken.end()) {

        if ((*itListToken).getType() == COMMENT) { itListToken++; continue; }


        /// RIGHTCURLY part -------------------------------------------------------------------
        else if ((*itListToken).getType() == RIGHTCURLY) {
            tempItListToken = itListToken;
            tempItListToken--;

            if ((*tempItListToken).getType() == LEFTCURLY) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", empty digraph detected"); return true; }

            itListToken++;
            if (itListToken == listToken.end()) {
                break;
            }
            else { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", unexpected token after RIGHTCURLY"); return true; }

        }
        else if ((*itListToken).getType() == SYMBOLE) { 
            //printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + (*itListToken).getValue() + " need to be a SYMBOL"); return true; 
            if ((*itListToken).getValue().length() >= maxStringLength) { printWarningMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", node name too long"); return true; }
            currentName = (*itListToken).getValue();

            itListToken++;
            if (itListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need a RIGHTCURLY, a LEFTSQUARE or an AFFECTATION"); return true; }

            /// RIGHTSQUARE part ------------------------------------------------------------------
            if ((*itListToken).getType() == LEFTSQUARE) {
                if (outputGraphDOT.count(currentName) != 0) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", symbole \"" + currentName + "\" is already defined"); return true; }

                currentType = GateType::NOTYPE;

                while ((*itListToken).getType() != RIGHTSQUARE && itListToken != listToken.end()) {
                    itListToken++;
                    if (itListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a KEYWORD"); return true; }
                    if ((*itListToken).getType() != KEYWORD) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a KEYWORD"); return true; }

                    if ((*itListToken).getValue() == "label") {

                        itListToken++;
                        if (itListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a EQUAL"); return true; }
                        if ((*itListToken).getType() != EQUAL) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a EQUAL"); return true; }

                        itListToken++;
                        if (itListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a TEXT"); return true; }
                        if ((*itListToken).getType() != TEXT) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a TEXT"); return true; }

                        currentType = ConvertStringToGateType((*itListToken).getValue());
                        itListToken++;
                    }
                    else {
                        printWarningMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", unexpected " + (*itListToken).getTypeString() + " \"" + (*itListToken).getValue() + "\"");
                    }
                }

                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SEMICOLON"); return true; }
                if ((*itListToken).getType() != SEMICOLON) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SEMICOLON"); return true; }


                /// Create a gate depending of his type and insert it in outputGraphDOT
                switch (currentType) {
                case GateType::INPUT:
                    outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateInput(currentName))); break;
                case GateType::OUTPUT:
                    outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateOutput(currentName))); break;
                case GateType::AND:
                    outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateAnd(currentName))); break;
                case GateType::OR:
                    outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateOr(currentName))); break;
                case GateType::XOR:
                    outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateXor(currentName))); break;
                case GateType::NOT:
                    outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateNot(currentName))); break;
                case GateType::REGISTER:
                    outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateRegister(currentName))); break;
                default:
                    printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a label"); return true;
                }
                
                itListToken++;
            }
            /// AFFECTATION part ------------------------------------------------------------------
            else if ((*itListToken).getType() == AFFECTATION) {

                tempVector.clear();

                /// Before AFFECTATION ----------------------------------------
                tempItListToken = itListToken;
                tempItListToken--;

                if (tempItListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*tempItListToken).getLine()) + ", need a SYMBOLE"); return true; }
                if ((*tempItListToken).getType() != SYMBOLE) { printErrorMessage("In DOT parser, line " + to_string((*tempItListToken).getLine()) + ", need a SYMBOLE"); return true; }
                if (outputGraphDOT.count((*tempItListToken).getValue()) == 0) { printErrorMessage("In DOT parser, line " + to_string((*tempItListToken).getLine()) + ", symbole \"" + (*tempItListToken).getValue() + "\" is not defined"); return true; }
                if (find(tempVector.begin(), tempVector.end(), (*tempItListToken).getValue()) != tempVector.end()) { printErrorMessage("In DOT parser, line " + to_string((*tempItListToken).getLine()) + ", symbole \"" + (*tempItListToken).getValue() + "\" is already used in this line"); return true; }

                if (dynamic_cast<const LogicGateOutput*>(outputGraphDOT.find((*tempItListToken).getValue())->second) != nullptr) {
                    printErrorMessage("In DOT parser, line " + to_string((*tempItListToken).getLine()) + ", symbole \"" + (*tempItListToken).getValue() + "\" is an output, but affectation line must not start with an output"); return true;
                }
                tempVector.push_back(currentName);

                /// After AFFECTATION -----------------------------------------
                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SYMBOLE"); return true; }
                if ((*itListToken).getType() != SYMBOLE) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SYMBOLE"); return true; }
                if (outputGraphDOT.count((*itListToken).getValue()) == 0) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", symbole \"" + (*itListToken).getValue() + "\" is not defined"); return true; }
                if (find(tempVector.begin(), tempVector.end(), (*itListToken).getValue()) != tempVector.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", symbole \"" + (*itListToken).getValue() + "\" is already used in this line"); return true; }

                if (dynamic_cast<const LogicGateAnd*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    dynamic_cast<LogicGateAnd*>     (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                }
                else if (dynamic_cast<const LogicGateOr*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    dynamic_cast<LogicGateOr*>      (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                }
                else if (dynamic_cast<const LogicGateXor*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    dynamic_cast<LogicGateXor*>     (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                }
                else if (dynamic_cast<const LogicGateNot*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    dynamic_cast<LogicGateNot*>     (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                }
                else if (dynamic_cast<const LogicGateRegister*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    dynamic_cast<LogicGateRegister*>(outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                }
                else if (dynamic_cast<const LogicGateOutput*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    dynamic_cast<LogicGateOutput*>  (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                }
                else if (dynamic_cast<const LogicGateInput*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "cannot link an INPUT to another one"); return true;
                }
                else {
                    printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need a LOGIC GATE in order to link an INPUT to it"); return true;
                }

                currentName = (*itListToken).getValue();
                tempVector.push_back(currentName);

                itListToken++;
                while ((*itListToken).getType() != SEMICOLON && itListToken != listToken.end() && (*itListToken).getType() == AFFECTATION) {

                    if (itListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need an AFFECTATION"); return true; }
                    if ((*itListToken).getType() != AFFECTATION) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a AFFECTATION"); return true; }


                    /// After AFFECTATION -----------------------------------------
                    itListToken++;
                    if (itListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SYMBOLE"); return true; }
                    if ((*itListToken).getType() != SYMBOLE) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SYMBOLE"); return true; }
                    if (outputGraphDOT.count((*itListToken).getValue()) == 0) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", symbole \"" + (*itListToken).getValue() + "\" is not defined"); return true; }
                    if (find(tempVector.begin(), tempVector.end(), (*itListToken).getValue()) != tempVector.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", symbole \"" + (*itListToken).getValue() + "\" is already used in this line"); return true; }

                    if (dynamic_cast<const LogicGateAnd*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                        dynamic_cast<LogicGateAnd*>     (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                    }
                    else if (dynamic_cast<const LogicGateOr*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                        dynamic_cast<LogicGateOr*>      (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                    }
                    else if (dynamic_cast<const LogicGateXor*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                        dynamic_cast<LogicGateXor*>     (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                    }
                    else if (dynamic_cast<const LogicGateNot*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                        dynamic_cast<LogicGateNot*>     (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                    }
                    else if (dynamic_cast<const LogicGateRegister*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                        dynamic_cast<LogicGateRegister*>(outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                    }
                    else if (dynamic_cast<const LogicGateOutput*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                        dynamic_cast<LogicGateOutput*>  (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                    }
                    else if (dynamic_cast<const LogicGateInput*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                        printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "cannot link an INPUT to another one"); return true;
                    }
                    else {
                        printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need a LOGIC GATE in order to link an INPUT to it"); return true;
                    }

                    currentName = (*itListToken).getValue();
                    tempVector.push_back(currentName);

                    itListToken++;
                }

                tempItListToken = itListToken;
                tempItListToken--;

                if (dynamic_cast<const LogicGateInput*>(outputGraphDOT.find((*tempItListToken).getValue())->second) != nullptr) {
                    printErrorMessage("In DOT parser, line " + to_string((*tempItListToken).getLine()) + ", symbole \"" + (*tempItListToken).getValue() + "\" is an input, but affectation line must not end with an input"); return true;
                }
                itListToken++;
            }
            else { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + " need a LEFTSQUARE or an AFFECTATION"); return true; }

        }
        else { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", \"" + (*itListToken).getValue() + "\", need a RIGHTCURLY or a SYMBOLE"); return true; }

    }
    return false;
};

#endif

/*
                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SYMBOLE"); return true; }
                if ((*itListToken).getType() != SYMBOLE) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SYMBOLE"); return true; }
                if (outputGraphDOT.count((*itListToken).getValue) == 0) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", symbole \"" + (*itListToken).getValue() + "\" is not defined"); return true; }
                if (find(tempVector.begin(), tempVector.end(), (*itListToken).getValue()) == tempVector.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", symbole \"" + (*itListToken).getValue() + "\" is already used in this line"); return true; }

                tempVector.push_back((*itListToken).getValue());

                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SYMBOLE"); return true; }
                if ((*itListToken).getType() != SYMBOLE) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SYMBOLE"); return true; }
                */






                //if ((*tempItListToken).getType() != LEFTCURLY) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", empty digraph detected"); return true; }

                            //tempVector.clear();
                            /*
                            while ((*itListToken).getType() != SEMICOLON && itListToken != listToken.end()) {

                                itListToken++;
                                if (itListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SYMBOLE"); return true; }
                                if ((*itListToken).getType() != SYMBOLE) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SYMBOLE"); return true; }
                                if (outputGraphDOT.count((*itListToken).getValue) == 0) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", symbole \"" + (*itListToken).getValue() + "\" is not defined"); return true; }
                                if (find(tempVector.begin(), tempVector.end(), (*itListToken).getValue()) == tempVector.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", symbole \"" + (*itListToken).getValue() + "\" is already used in this line"); return true; }

                                if (tempVector.size() == 0) {
                                    if (dynamic_cast<const LogicGateOutput*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                                        printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", symbole \"" + (*itListToken).getValue() + "\" is an output, but affectation line must not start with an output"); return true;
                                    }
                                }

                                tempVector.push_back((*itListToken).getValue());

                                itListToken++;
                                if (itListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SYMBOLE"); return true; }
                                if ((*itListToken).getType() != SYMBOLE) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", need a SYMBOLE"); return true; }


                            }*/



                            /*
                            if (dynamic_cast<const LogicGateAnd*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                                dynamic_cast<LogicGateAnd*>     (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                            }
                            else if (dynamic_cast<const LogicGateOr*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                                dynamic_cast<LogicGateOr*>      (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                            }
                            else if (dynamic_cast<const LogicGateXor*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                                dynamic_cast<LogicGateXor*>     (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                            }
                            else if (dynamic_cast<const LogicGateNot*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                                dynamic_cast<LogicGateNot*>     (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                            }
                            else if (dynamic_cast<const LogicGateRegister*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                                dynamic_cast<LogicGateRegister*>(outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                            }
                            else if (dynamic_cast<const LogicGateOutput*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                                dynamic_cast<LogicGateOutput*>  (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
                            }
                            else if (dynamic_cast<const LogicGateInput*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                                printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "cannot link an INPUT to another one"); return true;
                            }
                            else {
                                printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need a LOGIC GATE in order to link an INPUT to it"); return true;
                            }*/





/*
            /// Si le nom du node existe déjà -> on passe à l'affectation, sinon erreur dans la suite
        if (outputGraphDOT.count(currentName) == 1) break;
        //if (outputGraphDOT.count(currentName) != 0) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", symbole \"" + (*itListToken).getValue() + "\" is already defined"); return true; }
        currentName = (*itListToken).getValue();
        itListToken++;

        if ((*itListToken).getType() != LEFTSQUARE) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need a LEFTSQUARE"); return true; }
        itListToken++;

        if ((*itListToken).getType() != KEYWORD) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need a KEYWORD"); return true; }
        */
        // ----------------------------------------------------------------------------------------
        /*
        while (itListToken != listToken.end() && (*itListToken).getType() != RIGHTSQUARE) {
            if ((*itListToken).getValue() == "label") {
                itListToken++;
                if ((*itListToken).getType() != EQUAL) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need an EQUAL"); return true; }
                itListToken++;
                if ((*itListToken).getType() != TEXT) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need a TEXT"); return true; }
                type = ConvertStringToGateType((*itListToken).getValue());
                itListToken++;
            }
            if ((*itListToken).getValue() == "shape") {
                itListToken++;
                if ((*itListToken).getType() != EQUAL) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need an EQUAL"); return true; }
                itListToken++;
                if ((*itListToken).getType() != TEXT) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need a TEXT"); return true; }
                itListToken++;
            }
            if ((*itListToken).getType() == LEFTSQUARE) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need an RIGHTSQUARE"); return true; }
        }*/

        // ----------------------------------------------------------------------------------------
        /*
            /// Create a gate depending of his type and insert it in outputGraphDOT
        switch (type) {
        case INPUT:
            outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateInput(currentName))); break;
        case OUTPUT:
            outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateOutput(currentName))); break;
        case AND:
            outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateAnd(currentName))); break;
        case OR:
            outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateOr(currentName))); break;
        case XOR:
            outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateXor(currentName))); break;
        case NOT:
            outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateNot(currentName))); break;
        case REGISTER:
            outputGraphDOT.insert(pair<string, LogicGateBase*>(currentName, new LogicGateRegister(currentName))); break;
        default:
            printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need a label"); return true;

            if ((*itListToken).getType() != SEMICOLON) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need a SEMICOLON"); return true; }
        }*/

        // ----------------------------------------------------------------------------------------
                   /*
        while (itListToken != listToken.end()) {
            currentName = (*itListToken).getValue();
            itListToken++;
            if (itListToken == listToken.end()) break;

            if ((*itListToken).getType() == SEMICOLON) {

                if ((itGraphDOT = outputGraphDOT.find(currentName)) == outputGraphDOT.end()) { printErrorMessage("Can not find the element \"" + name + "\" inside of outputGraphDOT"); break; }

                if (dynamic_cast<const LogicGateInput*>(itGraphDOT->second) != nullptr) {
                    printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "cannot finish line without affecting INPUT");
                    return true;
                }
                itListToken++;
                if (itListToken == listToken.end()) break;

                if ((*itListToken).getType() == RIGHTCURLY) {
                    if (itListToken != listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "dot file must end after RIGHTCURLY"); return true; }
                    return false;
                }
                currentName = (*itListToken).getValue();
                cout << "3" << endl;
                itListToken++;
            }

            if ((*itListToken).getType() == LEFTSQUARE) {
                if (outputGraphDOT.count(currentName) == 1) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "node " + currentName + " already exists"); return true; }
                //Si on a une node définie 2x -> erreur
                printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " impossible to define node " + currentName + " during affectation"); return true;
                //Si une nouvelle node est définie pendant l'affectation -> erreur
            }

            if ((*itListToken).getType() != AFFECTATION) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need an AFFECTATION"); return true; }
            itListToken++;

            if (dynamic_cast<const LogicGateInput*>(outputGraphDOT.find((*itListToken).getValue())->second) == nullptr) {
                printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need an INPUT in order to affect to a LOGIC GATE");
                return true;
            }

            if ((*itListToken).getType() != SYMBOLE) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need an SYMBOLE"); return true; }

            if (dynamic_cast<const LogicGateAnd*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                dynamic_cast<LogicGateAnd*>     (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
            }
            else if (dynamic_cast<const LogicGateOr*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                dynamic_cast<LogicGateOr*>      (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
            }
            else if (dynamic_cast<const LogicGateXor*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                dynamic_cast<LogicGateXor*>     (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
            }
            else if (dynamic_cast<const LogicGateNot*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                dynamic_cast<LogicGateNot*>     (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
            }
            else if (dynamic_cast<const LogicGateRegister*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                dynamic_cast<LogicGateRegister*>(outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
            }
            else if (dynamic_cast<const LogicGateOutput*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                dynamic_cast<LogicGateOutput*>  (outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(currentName, outputGraphDOT.find(currentName)->second);
            }
            else if (dynamic_cast<const LogicGateInput*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "cannot link an INPUT to another one");
                return true;
            }
            else {
                printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need a LOGIC GATE in order to link an INPUT to it");
                return true;
            }

        }*/

        //if (itListToken != listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "file must end with RIGHTCURLY"); return true; }



/*
        itListToken++;
        if (itListToken != listToken.end()) {
            if ((*itListToken).getType() = RIGHTCURLY) {
                if ((*itListToken).getType() != COMMA) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need a COMMA"); return true; }
                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "unexpected COMMA"); return true; }
            }
            else if ((itListToken++) == listToken.end())
                return false;
        }
        else { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " need a RIGHTCURLY"); return true; }

        */