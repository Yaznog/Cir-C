#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "LogicGate.h"
#include "MessageManager.h"
#include "Toolbox.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;


class LogicCircuit {

public:

    LogicCircuit(map<string, LogicGateBase*> inputGates, const string& inputName = "Unnamed_circuit") : m_gates(inputGates), m_name(inputName) {

        /// Sort all LogicGateInput inside a map to have an easier way to access to them and get the size of the longuest input vector
        for (auto element : m_gates) {
            if (dynamic_cast<const LogicGateOutput*>(element.second) != nullptr) {
                
                m_outputs.insert(element);
            }
        }
        for (auto element : m_gates) m_maxOutputValues = max(m_maxOutputValues, element.second->getSizeOfOutputValues());
        for (auto element : m_gates) element.second->setSizeOfOutputValues(m_maxOutputValues);
    };

    void startSimulation() {
        for (unsigned int index = 1; index < m_maxOutputValues; index++) computeOutput(index);
        //for (auto element : m_outputs) printInConsoleLogicStateVector("Print wave of \"" + element.first + "\"", element.second->getAllOutput());        
    };

    inline const string getName()               const   { return this->m_name; };
    inline unsigned int getLastComputedIndex()  const   { return this->m_lastComputedIndex; };       

    string toString() { return "TODO"; }; // TODO

    void computeOutput(unsigned int index) {
        for (auto element : m_outputs) {
            element.second->computeOutput(index);
        }
    };

private:

    const string                    m_name;
    map<string, LogicGateBase*>     m_outputs;
    map<string, LogicGateBase*>     m_gates;
    unsigned int                    m_maxOutputValues = 1;
    unsigned int                    m_lastComputedIndex = 0;
};



#endif