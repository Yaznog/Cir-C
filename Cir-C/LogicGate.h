#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

enum LogicState {
    H,
    L,
    X,
    Z
};

LogicState operator&(LogicState& inputA, LogicState& inputB) {
    if (inputA == X || inputA == Z || inputB == X || inputB == Z)
        return X;
    if (inputA == H && inputB == H) 
        return H;
    else return L;
}

LogicState operator|(LogicState& inputA, LogicState& inputB) {
    if (inputA == X || inputA == Z || inputB == X || inputB == Z)
        return X;
    if(inputA == H || inputB == H)
        return H;
    else return L;
}

LogicState operator^(LogicState& inputA, LogicState& inputB) {
    if (inputA == X || inputA == Z || inputB == X || inputB == Z)
        return X;
    if(inputA == H != inputB == H)
        return H;
    else return L;
}

LogicState operator~(LogicState& inputA) {
    if (inputA == X || inputA == Z)
        return X;
    if(inputA == H)
        return L;
    else return H;
}


string convertLogicStateToString(LogicState inputLogicState) {
    switch (inputLogicState) {
    case H:
        return "-";
    case L:
        return "_";
    case X:
        return "X";
    case Z:
        return "Z";
    }
    return "U";
}


class LogicGateBase {

public:

    LogicGateBase(const string& inputId) : m_id(inputId) {};

    //string toString();

    inline const string getId() { return this->m_id; };
    inline const string getOutput() { return this->m_id; };

    //inline void setId(string inputValue) { this->m_id = inputValue; };
       
    virtual string computeOutput() = 0;

protected:

    const string m_id;
    map<string, LogicGateBase&> m_inputNodes;
    vector<LogicState> m_outputValues;
    
};




#endif