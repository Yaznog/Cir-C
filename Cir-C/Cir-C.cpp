#include "FileManager.h"
#include "Lexer.h"
#include "LogicGate.h"
#include "MessageManager.h"
#include "Parser.h"
#include "Simulator.h"
#include "Token.h"
#include "Toolbox.h"
#include "UnitTestingRoom.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{
    /// Beginning of the program --------------------------------------------------------------
    printInConsoleStartUpMessage(); /// Message wrote at the launch of the programm


    printDevMessage("branch devYaznog\n"); /// Message used to identified the development branch of the project

    //unitTestingLauncher(); /// Unit tests launcher

    string inputFilePathJSON = "";
    string inputFilePathDOT = "";
    string outputFilePathJSON = "";

    inputArgumentParser(argc, argv, inputFilePathJSON, inputFilePathDOT, outputFilePathJSON);

    /// Input files reading -------------------------------------------------------------------

    printInfoMessage("Input JSON file path: \"" + inputFilePathJSON + "\"");
    printInfoMessage("Input DOT file path: \"" + inputFilePathDOT + "\"");

    string extractedFileJSON = "";
    extractFile(inputFilePathJSON, extractedFileJSON);
    printInConsoleFileJSON(extractedFileJSON);

    string extractedFileDOT = "";
    extractFile(inputFilePathDOT, extractedFileDOT);
    printInConsoleFileDOT(extractedFileDOT);


    /// Lexer processing ----------------------------------------------------------------------

    list<Token> listTokenJSON;
    lexingInputStringJSON(extractedFileJSON, listTokenJSON); /// Input: extractedFileJSON; Output: listTokenJSON
    //printInConsoleListToken("Print listTokenJSON:", listTokenJSON);

    list<Token> listTokenDOT;
    lexingInputStringDOT(extractedFileDOT, listTokenDOT); /// Input: extractedFileDOT; Output: listTokenDOT
    //printInConsoleListToken("Print listTokenDOT:", listTokenDOT);         

        /// Parser processing ---------------------------------------------------------------------

    map<string, vector<LogicState>> graphJSON;
    parserInputTokenListJSON(listTokenJSON, graphJSON); /// Input: listTokenJSON; Output: graphJSON
    //printInConsoleMapWave("Print input waves:", graphJSON);

    string circuitName = "";
    map<string, LogicGateBase*> graphDOT;
    parserInputTokenListDOT(listTokenDOT, graphDOT, circuitName); /// Input: listTokenDOT; Output: graphDOT

        /// Simulator processing ------------------------------------------------------------------

    LogicCircuit* circuit = new LogicCircuit(graphDOT, graphJSON, circuitName);
    circuit->startSimulation();

    printInfoMessage("Circuit name = " + circuit->getName());
    //circuit->printAllWaves();
    circuit->printInputWaves();
    circuit->printOutputWaves();

    /// Output file writing -------------------------------------------------------------------

    map<string, vector<LogicState>> outputGraphJSON;
    circuit->getOutputGraphJSON(outputGraphJSON);
    string outputFileJSON = "";
    //convertJSONWaveToString(graphJSON, outputFileJSON);
    convertJSONWaveToString(outputGraphJSON, graphJSON, outputFileJSON);
    createFile(outputFilePathJSON, outputFileJSON);

    /// End of the program --------------------------------------------------------------------

    printInConsoleStopDownpMessage();

    return 0;
}