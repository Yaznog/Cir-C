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

/// -----------------------------------------------------------------------------------------------
///
/// The purpose of the class LogicCircuit is to gather all LogicGateBase and all waves into one 
/// entity and to control the simulation of the virtual circuit
///
/// -----------------------------------------------------------------------------------------------


class LogicCircuit {

public:

    LogicCircuit(map<string, LogicGateBase*> inputGates, map<string, vector<LogicState>> inputWaves, const string& inputName = "Unnamed_circuit") : m_gates(inputGates), m_name(inputName) {

        map<string, vector<LogicState>>::iterator itInputWaves;

            /// Sort all LogicGateInput inside a map to have an easier way to access to them and get the size of the longuest input vector
        for (auto element : m_gates) {
            if (dynamic_cast<const LogicGateOutput*>(element.second) != nullptr) {
                m_outputs.insert(element);
            }
                /// Launch the computing of all circuit outputs for one cycle
            else if (dynamic_cast<const LogicGateInput*>(element.second) != nullptr) {
                if ((itInputWaves = inputWaves.find(element.first)) == inputWaves.end()) printErrorMessage("Can not find the element \"" + element.first + "\" inside of inputGraphJSON");
                else dynamic_cast<LogicGateInput*>	(inputGates.find(element.first)->second)->affectOutputValues(itInputWaves->second);
            }
        }
        for (auto element : m_gates) m_maxOutputValues = max(m_maxOutputValues, element.second->getSizeOfOutputValues());
        for (auto element : m_gates) element.second->setSizeOfOutputValues(m_maxOutputValues);
    };

        /// Launch the computing of all circuit outputs for all cycles
    void startSimulation() {
        for (unsigned int index = 1; index < m_maxOutputValues; index++) computeOutput(index);
    };

    inline const string getName()               const   { return this->m_name; };
    inline unsigned int getLastComputedIndex()  const   { return this->m_lastComputedIndex; };       


        /// Launch the computing of all circuit outputs for one cycle
    void computeOutput(unsigned int index) {
        for (auto element : m_outputs) {
            element.second->computeOutput(index);
        }
    };

        /// Return a map of all circuit output gate outputs
    void getOutputGraphJSON(map<string, vector<LogicState>>& graphJSON) {
        for (auto element : m_outputs) {
            graphJSON.insert(pair<string, vector<LogicState>>{element.first, element.second->getAllOutput()});
        }
    }

        /// Return a map of all circuit input gate outputs
    void getInputGraphJSON(map<string, vector<LogicState>>& graphJSON) {
        for (auto element : m_gates) {
            if (dynamic_cast<const LogicGateInput*>(element.second) != nullptr) {
                graphJSON.insert(pair<string, vector<LogicState>>{element.first, element.second->getAllOutput()});
            }
        }
    }

        /// Return a map of all circuit gate outputs 
    void getGateGraphJSON(map<string, vector<LogicState>>& graphJSON) {
        for (auto element : m_gates) {       
            graphJSON.insert(pair<string, vector<LogicState>>{element.first, element.second->getAllOutput()});
        }
    }

        /// Print in consol all circuit output gate outputs
    void printOutputWaves() {
        map<string, vector<LogicState>> outputGraphJSON;
        getOutputGraphJSON(outputGraphJSON);
        printInConsoleMapWave("Print output waves:", outputGraphJSON);

    };

        /// Print in consol all circuit input gate outputs
    void printInputWaves() {
        map<string, vector<LogicState>> inputGraphJSON;
        getInputGraphJSON(inputGraphJSON);
        printInConsoleMapWave("Print input waves:", inputGraphJSON);

    };
        
        /// Print in consol all circuit gate outputs
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