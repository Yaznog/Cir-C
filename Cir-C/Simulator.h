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

    LogicCircuit(map<string, LogicGateBase*> inputGates, map<string, vector<LogicState>> inputWaves, const string& inputName = "Unnamed_circuit") : m_gates(inputGates), m_name(inputName) {

        map<string, vector<LogicState>>::iterator itInputWaves;

            /// Sort all LogicGateInput inside a map to have an easier way to access to them and get the size of the longuest input vector
        for (auto element : m_gates) {
            if (dynamic_cast<const LogicGateOutput*>(element.second) != nullptr) {
                m_outputs.insert(element);
            }
            else if (dynamic_cast<const LogicGateInput*>(element.second) != nullptr) {
                if ((itInputWaves = inputWaves.find(element.first)) == inputWaves.end()) printErrorMessage("Can not find the element \"" + element.first + "\" inside of inputGraphJSON");
                else dynamic_cast<LogicGateInput*>	(inputGates.find(element.first)->second)->affectOutputValues(itInputWaves->second);
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

    void getOutputGraphJSON(map<string, vector<LogicState>>& graphJSON) {
        for (auto element : m_outputs) {
            graphJSON.insert(pair<string, vector<LogicState>>{element.first, element.second->getAllOutput()});
        }
    }

    void getInputGraphJSON(map<string, vector<LogicState>>& graphJSON) {
        for (auto element : m_gates) {
            if (dynamic_cast<const LogicGateInput*>(element.second) != nullptr) {
                graphJSON.insert(pair<string, vector<LogicState>>{element.first, element.second->getAllOutput()});
            }
        }
    }

    void getGateGraphJSON(map<string, vector<LogicState>>& graphJSON) {
        for (auto element : m_gates) {       
            graphJSON.insert(pair<string, vector<LogicState>>{element.first, element.second->getAllOutput()});
        }
    }

    void printOutputWaves() {
        map<string, vector<LogicState>> outputGraphJSON;
        getOutputGraphJSON(outputGraphJSON);
        printInConsoleMapWave("Print output waves:", outputGraphJSON);

    };

    void printInputWaves() {
        map<string, vector<LogicState>> inputGraphJSON;
        getInputGraphJSON(inputGraphJSON);
        printInConsoleMapWave("Print input waves:", inputGraphJSON);

    };
    
    void printAllWaves() {
        map<string, vector<LogicState>> gateGraphJSON;
        getGateGraphJSON(gateGraphJSON);
        printInConsoleMapWave("Print gate waves:", gateGraphJSON);
    };

private:

    const string                    m_name;
    map<string, LogicGateBase*>     m_outputs;
    map<string, LogicGateBase*>     m_gates;
    unsigned int                    m_maxOutputValues = 1;
    unsigned int                    m_lastComputedIndex = 0;
};



#endif