#ifndef LOGICGATE_H
#define LOGICGATE_H

#include "MessageManager.h"
#include "Toolbox.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

inline void printErrorMessage(const string& inputString);
inline void printWarningMessage(const string& inputString);
inline void printInfoMessage(const string& inputString);
inline void printDevMessage(const string& inputString);

enum class LogicState {
    H,
    L,
    X,
    Z
};

LogicState operator&(const LogicState& inputA, const LogicState& inputB) {
    if ((inputA == LogicState::X) || (inputA == LogicState::Z) || (inputB == LogicState::X) || (inputB == LogicState::Z))
        return LogicState::X;
    if ((inputA == LogicState::H) && (inputB == LogicState::H))
        return LogicState::H;
    else return LogicState::L;
}

LogicState operator|(const LogicState& inputA, const LogicState& inputB) {
    if ((inputA == LogicState::X) || (inputA == LogicState::Z) || (inputB == LogicState::X) || (inputB == LogicState::Z))
        return LogicState::X;
    if((inputA == LogicState::H) || (inputB == LogicState::H))
        return LogicState::H;
    else return LogicState::L;
}

LogicState operator^(const LogicState& inputA, const LogicState& inputB) {
    if ((inputA == LogicState::X) || (inputA == LogicState::Z) || (inputB == LogicState::X) || (inputB == LogicState::Z))
        return LogicState::X;
    if((inputA == LogicState::H) != (inputB == LogicState::H))
        return LogicState::H;
    else return LogicState::L;
}

LogicState operator~(const LogicState& inputA) {
    if ((inputA == LogicState::X) || (inputA == LogicState::Z))
        return LogicState::X;
    if(inputA == LogicState::H)
        return LogicState::L;
    else return LogicState::H;
}

string convertLogicStateToString(LogicState inputLogicState) {
    switch (inputLogicState) {
    case LogicState::H:
        return "-";
    case LogicState::L:
        return "_";
    case LogicState::X:
        return "X";
    case LogicState::Z:
        return "Z";
    }
    return "U";
}


class LogicGateBase {

public:

    LogicGateBase(const string& inputName) : m_name(inputName) {}; 

    inline const string getName()                   const   { return this->m_name; };
    const vector<LogicState>& getAllOutput()        const   { return this->m_outputValues; };
    inline const LogicState& getLastOutput()        const   { return this->m_outputValues.back(); };

    void setSizeOfOutputValues(unsigned int size)    { 
        unsigned int previousSize = getSizeOfOutputValues();
        this->m_outputValues.resize(size);
        if (size > previousSize) {
            for (unsigned int index = previousSize; index < size; index++) {
                m_outputValues[index] = m_outputValues[index - 1];
            }
        }
        
    };
    inline unsigned int getSizeOfOutputValues()     const   { return (unsigned int)this->m_outputValues.size(); };

    virtual inline string toString() = 0;
           
    virtual LogicState computeOutput(unsigned int index) = 0;    

protected:

    const string        m_name;    
    vector<LogicState>  m_outputValues = { LogicState::X };
    unsigned int        m_deltaCycleCounter = 0;
    unsigned int        m_lastComputedIndex = 0;
    const unsigned int  m_deltaCycleMax = 10;
};


class LogicGateAnd : public LogicGateBase {
public:
    LogicGateAnd(const string& inputId) : LogicGateBase(inputId) {};

    inline void addInputNode(string& inputNodeName, LogicGateBase* inputNodeAdd) { m_inputNodes.insert({ inputNodeName, inputNodeAdd }); }

    inline unsigned int getNumberOfInputNode() const { return (unsigned int)m_inputNodes.size(); };

    inline string toString() { return ("And gate \"" + this->getName() + "\""); }; 

    LogicState computeOutput(unsigned int index) {
        if (index <= this->m_lastComputedIndex) return m_outputValues[index];
        if (m_inputNodes.size() < 2) { printErrorMessage("Not enought input node for door \"" + this->getName() + "\""); return LogicState::Z; }
        if (m_deltaCycleCounter >= m_deltaCycleMax) { printWarningMessage("Delta cycle max exceeds in the door \"" + this->getName() + "\""); return LogicState::X; }
        m_deltaCycleCounter++;

        LogicState tempValue = LogicState::H; // 'H' logic state is the neutral element for "And" door
        for (auto element : m_inputNodes) tempValue = tempValue & element.second->computeOutput(index);

        m_outputValues[index] = tempValue;
        m_lastComputedIndex = index;
        m_deltaCycleCounter = 0;
        return tempValue;
    };

private:
    map<string, LogicGateBase*> m_inputNodes;
};


class LogicGateOr : public LogicGateBase {
public:
    LogicGateOr(const string& inputId) : LogicGateBase(inputId) {};

    inline void addInputNode(string& inputNodeName, LogicGateBase* inputNodeAdd) { m_inputNodes.insert({ inputNodeName, inputNodeAdd }); }

    inline string toString() { return ("Or gate \"" + this->getName() + "\""); };

    LogicState computeOutput(unsigned int index) {
        if (index <= this->m_lastComputedIndex) return m_outputValues[index];
        if (m_inputNodes.size() < 2) { printErrorMessage("Not enought input node for door \"" + this->getName() + "\""); return LogicState::Z; }
        if (m_deltaCycleCounter >= m_deltaCycleMax) { printWarningMessage("Delta cycle max exceeds in the door \"" + this->getName() + "\""); return LogicState::X; }
        m_deltaCycleCounter++;

        LogicState tempValue = LogicState::L; // 'L' logic state is the neutral element for "Or" door
        for (auto element : m_inputNodes) tempValue = tempValue | element.second->computeOutput(index);

        m_outputValues[index] = tempValue;
        m_lastComputedIndex = index;
        m_deltaCycleCounter = 0;
        return tempValue;
    };

private:
    map<string, LogicGateBase*> m_inputNodes;
};


class LogicGateXor : public LogicGateBase {
public:
    LogicGateXor(const string& inputId) : LogicGateBase(inputId) {};

    inline void addInputNode(string& inputNodeName, LogicGateBase* inputNodeAdd) { m_inputNodes.insert({ inputNodeName, inputNodeAdd }); }

    inline string toString() { return ("Xor gate \"" + this->getName() + "\""); };

    LogicState computeOutput(unsigned int index) {
        if (index <= this->m_lastComputedIndex) return m_outputValues[index];
        if (m_inputNodes.size() < 2) { printErrorMessage("Not enought input node for door \"" + this->getName() + "\""); return LogicState::Z; }
        if (m_deltaCycleCounter >= m_deltaCycleMax) { printWarningMessage("Delta cycle max exceeds in the door \"" + this->getName() + "\""); return LogicState::X; }
        m_deltaCycleCounter++;

        LogicState tempValue = LogicState::L; // 'L' logic state is the neutral element for "Xor" door
        for (auto element : m_inputNodes) tempValue = tempValue ^ element.second->computeOutput(index);

        m_outputValues[index] = tempValue;
        m_lastComputedIndex = index;
        m_deltaCycleCounter = 0;
        return tempValue;
    };

private:
    map<string, LogicGateBase*> m_inputNodes;
};


class LogicGateNot : public LogicGateBase {
public:
    LogicGateNot(const string& inputId) : LogicGateBase(inputId) {};

    inline void addInputNode(string& inputNodeName, LogicGateBase* inputNodeAdd) { m_inputNodes.insert({ inputNodeName, inputNodeAdd }); };

    inline string toString() { return ("Not gate \"" + this->getName() + "\""); };

    LogicState computeOutput(unsigned int index) {
        if (index <= this->m_lastComputedIndex) return m_outputValues[index];
        if (m_inputNodes.size() != 1) { printErrorMessage("Need only one input node for door \"" + this->getName() + "\""); return LogicState::Z; }
        if (m_deltaCycleCounter >= m_deltaCycleMax) { printWarningMessage("Delta cycle max exceeds in the door \"" + this->getName() + "\""); return LogicState::X; }
        m_deltaCycleCounter++;

        LogicState tempValue = LogicState::X;
        for (auto element : m_inputNodes) tempValue = ~element.second->computeOutput(index);

        m_outputValues[index] = tempValue;
        m_lastComputedIndex = index;
        m_deltaCycleCounter = 0;
        return tempValue;
    };

private:
    map<string, LogicGateBase*> m_inputNodes;
};


class LogicGateInput : public LogicGateBase {
public:
    LogicGateInput(const string& inputId) : LogicGateBase(inputId) {};

    void affectOutputValues(vector<LogicState> inputValues) { this->m_outputValues = inputValues; };

    inline string toString() { return ("Input gate \"" + this->getName() + "\""); };

    LogicState computeOutput(unsigned int index) { return this->m_outputValues[index]; };
};


class LogicGateOutput : public LogicGateBase {
public:
    LogicGateOutput(const string& inputId) : LogicGateBase(inputId) {};

    inline void addInputNode(string& inputNodeName, LogicGateBase* inputNodeAdd) { m_inputNodes.insert({ inputNodeName, inputNodeAdd }); };

    inline string toString() { return ("Output gate \"" + this->getName() + "\""); };

    LogicState computeOutput(unsigned int index) {
        if (index <= this->m_lastComputedIndex) return m_outputValues[index];
        if (m_inputNodes.size() != 1) { printErrorMessage("Need only one input node for door \"" + this->getName() + "\""); return LogicState::Z; }
        if (m_deltaCycleCounter >= m_deltaCycleMax) { printWarningMessage("Delta cycle max exceeds in the door \"" + this->getName() + "\""); return LogicState::X; }
        m_deltaCycleCounter++;

        LogicState tempValue = LogicState::X;
        for (auto element : m_inputNodes) tempValue = element.second->computeOutput(index);

        m_outputValues[index] = tempValue;
        m_lastComputedIndex = index;
        m_deltaCycleCounter = 0;
        return tempValue;
    };

private:
    map<string, LogicGateBase*> m_inputNodes;
};


class LogicGateRegister : public LogicGateBase {
public:
    LogicGateRegister(const string& inputId) : LogicGateBase(inputId) {};

    inline void addInputNode(string& inputNodeName, LogicGateBase* inputNodeAdd) { m_inputNodes.insert({ inputNodeName, inputNodeAdd }); };

    inline string toString() { return ("Register gate \"" + this->getName() + "\""); };

    LogicState computeOutput(unsigned int index) {
        if (index <= this->m_lastComputedIndex) return m_outputValues[index];
        if (m_inputNodes.size() != 1) { printErrorMessage("Need only one input node for door \"" + this->getName() + "\""); return LogicState::Z; }
        if (m_deltaCycleCounter >= m_deltaCycleMax) { printWarningMessage("Delta cycle max exceeds in the door \"" + this->getName() + "\""); return LogicState::X; }
        m_deltaCycleCounter++;

        LogicState tempValue = LogicState::X;
        for (auto element : m_inputNodes) tempValue = element.second->computeOutput(index - 1);

        m_outputValues[index] = tempValue;
        m_lastComputedIndex = index;
        m_deltaCycleCounter = 0;
        return tempValue;
    };

private:
    map<string, LogicGateBase*> m_inputNodes;
};

#endif