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

enum GateType {
    INPUT,
    OUTPUT,
    AND,
    OR,
    XOR,
    NOT,
    REGISTER,
    NOTYPE
};


void convertJSONWaveToLogicState(const string& inputString, vector<LogicState>& outputVector) {
    // '=' not implemented

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
            if ((*itListToken).getType() != KEYWORD) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a KEYWORD"); return true; }
            
            if ((*itListToken).getValue() == "\"name\"" || (*itListToken).getValue() == "\'name\'" || (*itListToken).getValue() == "name") {
                
                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a COLON"); return true; }
                if ((*itListToken).getType() != COLON) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a COLON"); return true; }
                
                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a TEXT"); return true; }
                if ((*itListToken).getType() != TEXT) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a TEXT"); return true; }

                name = (*itListToken).getValue().substr(1, (*itListToken).getValue().length() - 2);
                
                itListToken++;
                if (itListToken != listToken.end()) {                    
                    if ((*itListToken).getType() != COMMA) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a COMMA"); return true; }
                    itListToken++;
                    if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "unexpected COMMA"); return true; }
                }
            }
            else if ((*itListToken).getValue() == "\"wave\"" || (*itListToken).getValue() == "\'wave\'" || (*itListToken).getValue() == "wave") {

                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a COLON"); return true; }
                if ((*itListToken).getType() != COLON) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a COLON"); return true; }
                
                itListToken++;
                if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a TEXT"); return true; }
                if ((*itListToken).getType() != TEXT) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a TEXT"); return true; }

                convertJSONWaveToLogicState((*itListToken).getValue().substr(1, (*itListToken).getValue().length() - 2), logicState);
                
                itListToken++;
                if (itListToken != listToken.end()) {                    
                    if ((*itListToken).getType() != COMMA) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a COMMA"); return true; }
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
            if ((*itListToken).getType() != COMMA) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a COMMA"); return true; }
            itListToken++;
            if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "unexpected COMMA"); return true; }
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

        if ((*itListToken).getType() != KEYWORD) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a KEYWORD"); return true; }
        
        if ((*itListToken).getValue() == "\"signal\"") {
            itListToken++;
            if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a COLON"); return true; }
            if ((*itListToken).getType() != COLON) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a COLON"); return true; }
            
            itListToken++;
            if (itListToken == listToken.end()) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a LEFTSQUARE"); return true; }
            if ((*itListToken).getType() != LEFTSQUARE) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a LEFTSQUARE"); return true; }
            
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
                if ((*itListToken).getType() != COMMA) { printErrorMessage("In JSON parser, line " + to_string((*itListToken).getLine()) + ", " + "need a COMMA"); return true; }
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


GateType ConvertStringToGateType(string type) {
    if (type == "INPUT") return INPUT;
    if (type == "OUTPUT") return OUTPUT;
    if (type == "AND") return AND;
    if (type == "OR") return OR;
    if (type == "XOR") return XOR;
    if (type == "NOT") return NOT;
    if (type == "REGISTER") return REGISTER;
};




bool parserInputTokenListDOT(list<Token>& listToken, map<string, LogicGateBase*>& outputGraphDOT) {
    auto itListToken = listToken.begin();
    string circuitName = "";
    string name = "";
    GateType type = NOTYPE ;


    while ((*itListToken).getType() == COMMENT) itListToken++; //Tant que c'est un commentaire, on passe au token suivant

    if (itListToken == listToken.end()) { return true; } // ------------------------------------------

    if ((*itListToken).getValue() != "digraph") { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "DOT file must start with digraph"); return true; }
    itListToken++;
    //Si on n'a pas "digraph" pour commencer -> erreur
    if ((*itListToken).getType() == SYMBOLE) {
        if ((*itListToken).getValue().length() >= 10) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "digraph name too long"); return true; }
        circuitName = (*itListToken).getValue();
        itListToken++;
    }
    //Si le digraph a un nom, on l'enregistre puis on passe à la suite
    if ((*itListToken).getType() != LEFTCURLY) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need a LEFTCURLY"); return true; }
    //s'il n'y a pas de { -> erreur
    itListToken++;

    if (itListToken == listToken.end()) { return true; } // ----------------------------------------------

    while (itListToken != listToken.end()) { //boucle de lecture des entrées sorties

        if ((*itListToken).getType() == COMMENT) { itListToken++; continue; }
        if ((*itListToken).getType() != SYMBOLE) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need a SYMBOL"); return true; }
        if ((*itListToken).getValue().length() >= 10) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "node name too long"); return true; }
        if (outputGraphDOT.count(name) == 1) break;
        // Si le nom du node existe déjà -> on passe à l'affectation, sinon erreur dans la suite
        name = (*itListToken).getValue();
        itListToken++;
        if ((*itListToken).getType() != LEFTSQUARE) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need a LEFTSQUARE"); return true; }
        itListToken++;

        if ((*itListToken).getType() != KEYWORD) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need a KEYWORD"); return true; }
        while (itListToken != listToken.end() && (*itListToken).getType() != RIGHTSQUARE) {
            if ((*itListToken).getValue() == "label") {
                itListToken++;
                if ((*itListToken).getType() != EQUAL) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need an EQUAL"); return true; }
                itListToken++;
                if ((*itListToken).getType() != TEXT) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need a TEXT"); return true; }
                type = ConvertStringToGateType((*itListToken).getValue());
                itListToken++;
            }
            if ((*itListToken).getValue() == "shape") {
                itListToken++;
                if ((*itListToken).getType() != EQUAL) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need an EQUAL"); return true; }
                itListToken++;
                if ((*itListToken).getType() != TEXT) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need a TEXT"); return true; }
                itListToken++;
            }
            if ((*itListToken).getType() == LEFTSQUARE) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need an RIGHTSQUARE"); return true; }

        }

        for (int i = 0; i < 10; i++) {
            switch (type) {
            case INPUT:
                outputGraphDOT.insert(pair<string, LogicGateBase*>(name, new LogicGateInput(name)));
                break;

            case OUTPUT:
                outputGraphDOT.insert(pair<string, LogicGateBase*>(name, new LogicGateOutput(name)));
                break;

            case AND:
                outputGraphDOT.insert(pair<string, LogicGateBase*>(name, new LogicGateAnd(name)));
                break;

            case OR:
                outputGraphDOT.insert(pair<string, LogicGateBase*>(name, new LogicGateOr(name)));
                break;

            case XOR:
                outputGraphDOT.insert(pair<string, LogicGateBase*>(name, new LogicGateXor(name)));
                break;

            case NOT:
                outputGraphDOT.insert(pair<string, LogicGateBase*>(name, new LogicGateNot(name)));
                break;

            case REGISTER:
                outputGraphDOT.insert(pair<string, LogicGateBase*>(name, new LogicGateRegister(name)));
                break;

            case UNKNOWN:
                printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need a label");
                return true;


                if ((*itListToken).getType() != SEMICOLON) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need a SEMICOLON"); return true; }
            }

            while (itListToken != listToken.end()) {
                name = (*itListToken).getValue();
                itListToken++;
                if ((*itListToken).getType() == SEMICOLON) {
                    if (dynamic_cast<const LogicGateInput*>(outputGraphDOT.find(name)->second) != nullptr) {
                        printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "cannot finish line without affecting INPUT"); 
                        return true; 
                    }
                    itListToken++;
                    if ((*itListToken).getType() == RIGHTCURLY) {
                        if (itListToken != listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "dot file must end after RIGHTCURLY"); return true; }
                        return false;
                    }
                    name = (*itListToken).getValue();
                    itListToken++;
                }
                if ((*itListToken).getType() == LEFTSQUARE) {
                    if (outputGraphDOT.count(name) == 1) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "node " + name + " already exists"); return true; }
                    //Si on a une node définie 2x -> erreur
                    printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + " impossible to define node " + name + " during affectation"); return true;
                    //Si une nouvelle node est définie pendant l'affectation -> erreur
                }

                if ((*itListToken).getType() != AFFECTATION) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need an AFFECTATION"); return true; }
                itListToken++;
                
                if (dynamic_cast<const LogicGateInput*>(outputGraphDOT.find((*itListToken).getValue())->second) == nullptr) {
                    printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need an INPUT in order to affect to a LOGIC GATE"); 
                    return true;
                }

                if ((*itListToken).getType() != SYMBOLE) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need an SYMBOLE"); return true; }

                if (dynamic_cast<const LogicGateAnd*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    dynamic_cast<LogicGateAnd*>(outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(name, outputGraphDOT.find(name)->second);
                }
                else if (dynamic_cast<const LogicGateOr*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    dynamic_cast<LogicGateOr*>(outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(name, outputGraphDOT.find(name)->second);
                }
                else if (dynamic_cast<const LogicGateXor*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    dynamic_cast<LogicGateXor*>(outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(name, outputGraphDOT.find(name)->second);
                }
                else if (dynamic_cast<const LogicGateNot*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    dynamic_cast<LogicGateNot*>(outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(name, outputGraphDOT.find(name)->second);
                }
                else if (dynamic_cast<const LogicGateRegister*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    dynamic_cast<LogicGateRegister*>(outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(name, outputGraphDOT.find(name)->second);
                }
                else if (dynamic_cast<const LogicGateOutput*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    dynamic_cast<LogicGateOutput*>(outputGraphDOT.find((*itListToken).getValue())->second)->addInputNode(name, outputGraphDOT.find(name)->second);
                }
                else if (dynamic_cast<const LogicGateInput*>(outputGraphDOT.find((*itListToken).getValue())->second) != nullptr) {
                    printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "cannot link an INPUT to another one"); 
                    return true;
                }
                else {
                    printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "need a LOGIC GATE in order to link an INPUT to it"); 
                    return true;
                }

            }

            if (itListToken != listToken.end()) { printErrorMessage("In DOT parser, line " + to_string((*itListToken).getLine()) + ", " + "file must end with RIGHTCURLY"); return true; }
        }
    }
    return false;
        
};

#endif