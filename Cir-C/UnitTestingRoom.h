#ifndef UNITTESTINGROOM_H
#define UNITTESTINGROOM_H

#include "Toolbox.h"
#include "FileManager.h"
#include "MessageManager.h"
#include "Lexer.h"
#include "Token.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

using namespace std;

	/// FileManager.h -----------------------------------------------------------------------------
bool unitTest_extractFile_DOT() {
	const string inputString = "C:\\Users\\Yaznog\\source\\repos\\Yaznog\\Cir-C\\testfiles\\testFileDot.dot";
	string outputString = "";
	const string expectedOutputString =
		"digraph test {\n    I1 [label = \"INPUT A\"];\n    I2 [label = \"INPUT B\"];\n    //I3 [label = \"INPUT C\"];\n    /*I4 [label = \"INPUT D\"];\n    I5 [label = \"INPUT E\"];*/\n    #I6 [label = \"INPUT F\"];\n    GATE [label = \"AND2\" shape=box];\n    O [label = \"OUTPUT\"];\n    I1 -> GATE -> O;\n    I2 -> GATE;\n}";
	
	extractFile(inputString, outputString);

	if (expectedOutputString == outputString)
		return false;
	else
		return true;
}

bool unitTest_extractFile_JSON() {
	const string inputString = "C:\\Users\\Yaznog\\source\\repos\\Yaznog\\Cir-C\\testfiles\\testFileJson.json";
	string outputString = "";
	const string expectedOutputString = "";

	extractFile(inputString, outputString);

	if (expectedOutputString == outputString)
		return false;
	else
		return true;
}

	/// Lexer.h -----------------------------------------------------------------------------------
bool unitTest_lexingInputStringDOT() {
	const string inputString = 
		"digraph test {\n    I1 [label = \"INPUT A\"];\n    I2 [label = \"INPUT B\"];\n    //I3 [label = \"INPUT C\"];\n    /*I4 [label = \"INPUT D\"];\n    I5 [label = \"INPUT E\"];*/\n    #I6 [label = \"INPUT F\"];\n    GATE [label = \"AND2\" shape=box];\n    O [label = \"OUTPUT\"];\n    I1 -> GATE -> O;\n    I2 -> GATE;\n}";
	list<Token> outputListToken;
	list<Token> expectedOutputListToken;	

	expectedOutputListToken.push_back(Token(KEYWORD,		"digraph",		1));
	expectedOutputListToken.push_back(Token(SYMBOLE,		"test",			1));
	expectedOutputListToken.push_back(Token(LEFTCURLY,		"{",			1));

	expectedOutputListToken.push_back(Token(SYMBOLE,		"I1",			2));
	expectedOutputListToken.push_back(Token(LEFTSQUARE,		"[",			2));
	expectedOutputListToken.push_back(Token(KEYWORD,		"label",		2));
	expectedOutputListToken.push_back(Token(EQUAL,			"=",			2));
	expectedOutputListToken.push_back(Token(TEXT,			"\"INPUT A\"",	2));
	expectedOutputListToken.push_back(Token(RIGHTSQUARE,	"]",			2));
	expectedOutputListToken.push_back(Token(SEMICOLON,		";",			2));

	expectedOutputListToken.push_back(Token(SYMBOLE,		"I2",			3));
	expectedOutputListToken.push_back(Token(LEFTSQUARE,		"[",			3));
	expectedOutputListToken.push_back(Token(KEYWORD,		"label",		3));
	expectedOutputListToken.push_back(Token(EQUAL,			"=",			3));
	expectedOutputListToken.push_back(Token(TEXT,			"\"INPUT B\"",	3));
	expectedOutputListToken.push_back(Token(RIGHTSQUARE,	"]",			3));
	expectedOutputListToken.push_back(Token(SEMICOLON,		";",			3));

	expectedOutputListToken.push_back(Token(COMMENT,		"//",			4));
	expectedOutputListToken.push_back(Token(SYMBOLE,		"I3",			4));
	expectedOutputListToken.push_back(Token(LEFTSQUARE,		"[",			4));
	expectedOutputListToken.push_back(Token(KEYWORD,		"label",		4));
	expectedOutputListToken.push_back(Token(EQUAL,			"=",			4));
	expectedOutputListToken.push_back(Token(TEXT,			"\"INPUT C\"",	4));
	expectedOutputListToken.push_back(Token(RIGHTSQUARE,	"]",			4));
	expectedOutputListToken.push_back(Token(SEMICOLON,		";",			4));

	expectedOutputListToken.push_back(Token(LEFTCOMMENT,	"/*",			5));
	expectedOutputListToken.push_back(Token(SYMBOLE,		"I4",			5));
	expectedOutputListToken.push_back(Token(LEFTSQUARE,		"[",			5));
	expectedOutputListToken.push_back(Token(KEYWORD,		"label",		5));
	expectedOutputListToken.push_back(Token(EQUAL,			"=",			5));
	expectedOutputListToken.push_back(Token(TEXT,			"\"INPUT D\"",	5));
	expectedOutputListToken.push_back(Token(RIGHTSQUARE,	"]",			5));
	expectedOutputListToken.push_back(Token(SEMICOLON,		";",			5));

	expectedOutputListToken.push_back(Token(SYMBOLE,		"I5",			6));
	expectedOutputListToken.push_back(Token(LEFTSQUARE,		"[",			6));
	expectedOutputListToken.push_back(Token(KEYWORD,		"label",		6));
	expectedOutputListToken.push_back(Token(EQUAL,			"=",			6));
	expectedOutputListToken.push_back(Token(TEXT,			"\"INPUT E\"",	6));
	expectedOutputListToken.push_back(Token(RIGHTSQUARE,	"]",			6));
	expectedOutputListToken.push_back(Token(SEMICOLON,		";",			6));
	expectedOutputListToken.push_back(Token(RIGHTCOMMENT,	"*/",			6));

	expectedOutputListToken.push_back(Token(HASH,			"#",			7));
	expectedOutputListToken.push_back(Token(SYMBOLE,		"I6",			7));
	expectedOutputListToken.push_back(Token(LEFTSQUARE,		"[",			7));
	expectedOutputListToken.push_back(Token(KEYWORD,		"label",		7));
	expectedOutputListToken.push_back(Token(EQUAL,			"=",			7));
	expectedOutputListToken.push_back(Token(TEXT,			"\"INPUT F\"",	7));
	expectedOutputListToken.push_back(Token(RIGHTSQUARE,	"]",			7));
	expectedOutputListToken.push_back(Token(SEMICOLON,		";",			7));

	expectedOutputListToken.push_back(Token(SYMBOLE,		"GATE",			8));
	expectedOutputListToken.push_back(Token(LEFTSQUARE,		"[",			8));
	expectedOutputListToken.push_back(Token(KEYWORD,		"label",		8));
	expectedOutputListToken.push_back(Token(EQUAL,			"=",			8));
	expectedOutputListToken.push_back(Token(TEXT,			"\"AND2\"",		8));
	expectedOutputListToken.push_back(Token(KEYWORD,		"shape",		8));
	expectedOutputListToken.push_back(Token(EQUAL,			"=",			8));
	expectedOutputListToken.push_back(Token(KEYWORD,		"box",			8));
	expectedOutputListToken.push_back(Token(RIGHTSQUARE,	"]",			8));
	expectedOutputListToken.push_back(Token(SEMICOLON,		";",			8));

	expectedOutputListToken.push_back(Token(SYMBOLE,		"O",			9));
	expectedOutputListToken.push_back(Token(LEFTSQUARE,		"[",			9));
	expectedOutputListToken.push_back(Token(KEYWORD,		"label",		9));
	expectedOutputListToken.push_back(Token(EQUAL,			"=",			9));
	expectedOutputListToken.push_back(Token(TEXT,			"\"OUTPUT\"",	9));
	expectedOutputListToken.push_back(Token(RIGHTSQUARE,	"]",			9));
	expectedOutputListToken.push_back(Token(SEMICOLON,		";",			9));

	expectedOutputListToken.push_back(Token(SYMBOLE,		"I1",			10));
	expectedOutputListToken.push_back(Token(AFFECTATION,	"->",			10));
	expectedOutputListToken.push_back(Token(SYMBOLE,		"GATE",			10));
	expectedOutputListToken.push_back(Token(AFFECTATION,	"->",			10));
	expectedOutputListToken.push_back(Token(SYMBOLE,		"O",			10));
	expectedOutputListToken.push_back(Token(SEMICOLON,		";",			10));

	expectedOutputListToken.push_back(Token(SYMBOLE,		"I2",			11));
	expectedOutputListToken.push_back(Token(AFFECTATION,	"->",			11));
	expectedOutputListToken.push_back(Token(SYMBOLE,		"GATE",			11));
	expectedOutputListToken.push_back(Token(SEMICOLON,		";",			11));

	expectedOutputListToken.push_back(Token(RIGHTCURLY,		"}",			12));

	lexingInputStringDOT(inputString, outputListToken);

	//printInConsoleListToken("Print outputListToken:", outputListToken);
	//printInConsoleListToken("Print expectedOutputListToken:", expectedOutputListToken);

	if (listsOfTokenAreEqual(outputListToken, expectedOutputListToken))
		return false;
	else
		return true;
}

	/// Toolbox.h ---------------------------------------------------------------------------------


	/// Launcher ----------------------------------------------------------------------------------
void unitTestingLauncher() {
	unsigned int errorNumber = 0;
	printInfoMessage("Unit test(s) are starting...\n");

	if (unitTest_extractFile_DOT()) { printErrorMessage("Error during the test of \"unitTest_extractFile_DOT()\""); errorNumber++; }
	else printInfoMessage("OK with the test of \"unitTest_extractFile_DOT()\"");

	if (unitTest_extractFile_JSON()) { printErrorMessage("Error during the test of \"unitTest_extractFile_JSON()\""); errorNumber++; }
	else printInfoMessage("OK with the test of \"unitTest_extractFile_JSON()\"");

	if (unitTest_lexingInputStringDOT()) { printErrorMessage("Error during the test of \"unitTest_lexingInputStringDOT()\""); errorNumber++; }
	else printInfoMessage("OK with the test of \"unitTest_lexingInputStringDOT()\"");

	printInfoMessage("Unit test(s) ended with " + to_string(errorNumber) + " error(s)");
}


#endif