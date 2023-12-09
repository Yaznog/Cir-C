#include "FileManager.h"
#include "MessageManager.h"
#include "Lexer.h"
#include "Token.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

#include <vector>

using namespace std;

const string listOfArgsinputFilePathJSON[4] = { "-ij", "-IJ", "--inputjson", "--INPUTJSON" };
const string listOfArgsinputFilePathDOT [4] = { "-id", "-ID", "--inputdot", "--INPUTDOT" };
const string listOfArgsHelp             [4] = { "-h", "-H", "--help", "--HELP" };

string inputFilePathJSON = "";
string inputFilePathDOT = "";


int inputArgumentParser(int argc, char* argv[]) {

    //int rowsNb = sizeof(listOfInputArgs) / sizeof(listOfInputArgs[0]);
    //int colsNb = sizeof(listOfInputArgs[0]) / sizeof(listOfInputArgs[0][0]);

    for (int i = 1; i < argc; i++) {
        //cout << "i = " << i << "   " << argv[i] << endl;
        if (find(begin(listOfArgsinputFilePathJSON), end(listOfArgsinputFilePathJSON), argv[i]) != end(listOfArgsinputFilePathJSON)) {
            if (i + 1 != argc) {
                inputFilePathJSON = argv[i + 1];
                i++;
            }
            else
                cout << "ERROR: input JSON file path is missing after \"" << argv[i] << "\"" << endl;            
        }

        else if (find(begin(listOfArgsinputFilePathDOT), end(listOfArgsinputFilePathDOT), argv[i]) != end(listOfArgsinputFilePathDOT)) {
            if (i + 1 != argc) {
                inputFilePathDOT = argv[i + 1];
                i++;
            }
            else
                cout << "ERROR: input JSON file path is missing after \"" << argv[i] << "\"" << endl;
        }

        else if(find(begin(listOfArgsHelp), end(listOfArgsHelp), argv[i]) != end(listOfArgsHelp)) {
            cout << "Args found" << endl;
        }
        
        else {
            cout << "Args not found: \"" << argv[i] << "\"" << endl;
        }
            
        //cout << find(begin(listOfArgsInputFile), end(listOfArgsInputFile), argv[i]) << endl;
    }
    cout << endl;

    return 0;
}


int main(int argc, char* argv[])
{
        /// Beginning of the program --------------------------------------------------------------
    printInConsoleStartUpMessage();

    if (inputArgumentParser(argc, argv)) {
        cout << "Error with input argument(s)" << endl;
    }

        /// Input files reading -------------------------------------------------------------------
    cout << "Input JSON file path: \"" << inputFilePathJSON << "\"" << endl;
    cout << "Input DOT file path: \"" << inputFilePathDOT << "\"" << endl;
                   
    string extractedFileJSON = "";
    extractFile(inputFilePathJSON, extractedFileJSON);
    printInConsoleFileJSON(extractedFileJSON);

    string extractedFileDOT = "";
    extractFile(inputFilePathDOT, extractedFileDOT);
    printInConsoleFileDOT(extractedFileDOT);

    /// Lexer processing ----------------------------------------------------------------------

    list<Token> listTokenJSON;
    lexingInputStringJSON(extractedFileJSON, listTokenJSON);
    //printInConsoleListToken("Print listTokenJSON:", listTokenJSON);
                                
    list<Token> listTokenDOT;
    lexingInputStringDOT(extractedFileDOT, listTokenDOT);
    printInConsoleListToken("Print listTokenDOT:", listTokenDOT);
        






        /// End of the program --------------------------------------------------------------------
    printInConsoleStopDownpMessage();

    return 0;
}