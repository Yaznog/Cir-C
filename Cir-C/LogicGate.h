#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

enum LogicState {
    1,
    0,
    X,
    Z
};

LogicState operator&(LogicState& inputA, LogicState& inputB) {
    if (inputA == X || inputA == Z || inputB == X || inputB == Z)
        return X;
    (inputA == 1 && inputB == 1) ? return 1 : return 0;
}

LogicState operator|(LogicState& inputA, LogicState& inputB) {
    if (inputA == X || inputA == Z || inputB == X || inputB == Z)
        return X;
    (inputA == 1 || inputB == 1) ? return 1 : return 0;
}

LogicState operator^(LogicState& inputA, LogicState& inputB) {
    if (inputA == X || inputA == Z || inputB == X || inputB == Z)
        return X;
    (inputA == 1 != inputB == 1) ? return 1 : return 0;
}

LogicState operator~(LogicState& inputA) {
    if (inputA == X || inputA == Z)
        return X;
    (inputA == 1) ? return 0 : return 1;
}


class LogicGateBase {

public:

    LogicGateBase(const string& inputId) : m_id(inputId) {};

        
    static string getStringType(const string& inputString) {
        return "nope";
    };

    string toString() { return this->convertTokenTypeToString(this->m_type) + " " + this->m_value + " " + to_string(this->m_line); };

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