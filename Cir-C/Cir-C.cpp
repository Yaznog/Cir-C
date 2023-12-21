#include "Toolbox.h"
#include "FileManager.h"
#include "MessageManager.h"
#include "Lexer.h"
#include "Parser.h"
#include "Token.h"
#include "LogicGate.h"
#include "Simulator.h"
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
    printInConsoleStartUpMessage();

    printDevMessage("branch devYaznog\n");

    unitTestingLauncher(); // Unit test(s)

    string inputFilePathJSON = "";
    string inputFilePathDOT = "";

    //inputArgumentParser(argc, argv, inputFilePathJSON, inputFilePathDOT);

        /// Input files reading -------------------------------------------------------------------

    //printInfoMessage("Input JSON file path: \"" + inputFilePathJSON + "\"");
    //printInfoMessage("Input DOT file path: \"" + inputFilePathDOT + "\"");
                   
    //string extractedFileJSON = "";
    //extractFile(inputFilePathJSON, extractedFileJSON);
    //printInConsoleFileJSON(extractedFileJSON);

    //string extractedFileDOT = "";
    //extractFile(inputFilePathDOT, extractedFileDOT);
    //printInConsoleFileDOT(extractedFileDOT);    

        /// Lexer processing ----------------------------------------------------------------------

    //list<Token> listTokenJSON;
    //lexingInputStringJSON(extractedFileJSON, listTokenJSON);
    //printInConsoleListToken("Print listTokenJSON:", listTokenJSON);
                                
    //list<Token> listTokenDOT;
    //lexingInputStringDOT(extractedFileDOT, listTokenDOT);
    //printInConsoleListToken("Print listTokenDOT:", listTokenDOT);         

        /// Parser processing ---------------------------------------------------------------------
                        
    map<string, vector<LogicState>> graphJSON;       
    //parserInputTokenListJSON(listTokenJSON, graphJSON);
    //printInConsoleMapWave("Print outputGraph:", graphJSON);

    map<string,LogicGateBase*> graphDOT;       
    //parserInputTokenListDOT(listTokenDOT, graphDOT);

        /// End of the program --------------------------------------------------------------------

    printInConsoleStopDownpMessage();

    return 0;
}