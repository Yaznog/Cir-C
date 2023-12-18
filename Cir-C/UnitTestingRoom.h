#ifndef UNITTESTINGROOM_H
#define UNITTESTINGROOM_H

#include "Toolbox.h"
#include "FileManager.h"
#include "MessageManager.h"
#include "Lexer.h"
#include "Parser.h"
#include "Token.h"
#include "LogicGate.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

using namespace std;

	/// FileManager.h -----------------------------------------------------------------------------
bool unitTest_extractFile_DOT() {
	const string inputString = "C:\\Users\\cedri\\source\\repos\\Yaznog\\Cir-C\\testfiles\\testFileDot.dot";
	string outputString = "";
	const string expectedOutputString = 
		"digraph test {\n    I1 [label = \"INPUT A\"];\n    I2 [label = \"INPUT B\"];\n    //I3 [label = \"INPUT C\"];\n    /*I4 [label = \"INPUT D\"];\n    I5 [label = \"INPUT E\"];*/\n    #I6 [label = \"INPUT F\"];\n    GATE [label = \"AND2\" shape=box];\n    O [label = \"OUTPUT\"];\n    I1 -> GATE -> O;\n    I2 -> GATE;\n}\n";
	
	extractFile(inputString, outputString);

	//createFile("expectedOutputString.txt", expectedOutputString);
	//createFile("outputString.txt", outputString);

	if (expectedOutputString == outputString)
		return false;
	else
		return true;
}


bool unitTest_extractFile_JSON() {
	
	const string inputString = "C:\\Users\\cedri\\source\\repos\\Yaznog\\Cir-C\\testfiles\\testFileJson.json";
	string outputString = "";
	const string expectedOutputString = "{\n  \"signal\": [\n    {\n      \"name\": \"INPUT A\",\n      \"wave\": \"l..h.\"\n    },\n    {\n      \"name\": \"INPUT B\",\n      \"wave\": \"l..h.\"\n    },\n    {\n      //\"name\": \"INPUT C\",\n      \"name\": \"INPUT D\",\n      \"wave\": \"l..h.\"\n    },/*\n    {\n      \"name\": \"INPUT E\",\n      \"wave\": \"l..h.\"\n    },*/\n    {\n      \'name\': \'INPUT F\',\n      \'wave\': \'l..h.\'\n    },\n    {\n      name: \"INPUT G\",\n      wave: \"l..h.\"\n    }\n  ]\n}\n";
		
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

	expectedOutputListToken.push_back(Token(COMMENT,		"//I3 [label = \"INPUT C\"];", 4));

	/*
	expectedOutputListToken.push_back(Token(COMMENT,		"//",			4));
	expectedOutputListToken.push_back(Token(SYMBOLE,		"I3",			4));
	expectedOutputListToken.push_back(Token(LEFTSQUARE,		"[",			4));
	expectedOutputListToken.push_back(Token(KEYWORD,		"label",		4));
	expectedOutputListToken.push_back(Token(EQUAL,			"=",			4));
	expectedOutputListToken.push_back(Token(TEXT,			"\"INPUT C\"",	4));
	expectedOutputListToken.push_back(Token(RIGHTSQUARE,	"]",			4));
	expectedOutputListToken.push_back(Token(SEMICOLON,		";",			4));*/
	   

	expectedOutputListToken.push_back(Token(COMMENT,		"/*I4 [label = \"INPUT D\"];\n    I5 [label = \"INPUT E\"];*/", 6));
	/*
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
	expectedOutputListToken.push_back(Token(RIGHTCOMMENT,	"*///",			6));
		
	expectedOutputListToken.push_back(Token(COMMENT,		"#I6 [label = \"INPUT F\"];", 7));
	
	/*
	expectedOutputListToken.push_back(Token(HASH,			"#",			7));
	expectedOutputListToken.push_back(Token(SYMBOLE,		"I6",			7));
	expectedOutputListToken.push_back(Token(LEFTSQUARE,		"[",			7));
	expectedOutputListToken.push_back(Token(KEYWORD,		"label",		7));
	expectedOutputListToken.push_back(Token(EQUAL,			"=",			7));
	expectedOutputListToken.push_back(Token(TEXT,			"\"INPUT F\"",	7));
	expectedOutputListToken.push_back(Token(RIGHTSQUARE,	"]",			7));
	expectedOutputListToken.push_back(Token(SEMICOLON,		";",			7));*/

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
	   
	//createFile("expectedOutputString.txt", expectedOutputString);
	//createFile("outputString.txt", outputString);

	unsigned int lineNumber;
	if ((lineNumber = listsOfTokenAreEqual(outputListToken, expectedOutputListToken)) != 0) {
		printErrorMessage("Lists of Token are different at line " + to_string(lineNumber));
		return true;
	}
	else
		return false;
}


bool unitTest_lexingInputStringJSON() {
	const string inputString =
		"{\n  \"signal\": [\n    {\n      \"name\": \"INPUT A\",\n      \"wave\": \"l..h.\"\n    },\n    {\n      \"name\": \"INPUT B\",\n      \"wave\": \"l..h.\"\n    },\n    {\n      //\"name\": \"INPUT C\",\n      \"name\": \"INPUT D\",\n      \"wave\": \"l..h.\"\n    },/*\n    {\n      \"name\": \"INPUT E\",\n      \"wave\": \"l..h.\"\n    }*/\n    {\n      \'name\': \'INPUT F\',\n      \'wave\': \'l..h.\'\n    },\n    {\n      name: \"INPUT G\",\n      wave: \"l..h.\"\n    }\n  ]\n}\n";
	list<Token> outputListToken;
	list<Token> expectedOutputListToken;

	expectedOutputListToken.push_back(Token(LEFTCURLY,		"{",			1));

	expectedOutputListToken.push_back(Token(KEYWORD,		"\"signal\"",	2));
	expectedOutputListToken.push_back(Token(COLON,			":",			2));
	expectedOutputListToken.push_back(Token(LEFTSQUARE,		"[",			2));


	expectedOutputListToken.push_back(Token(LEFTCURLY,		"{",			3));

	expectedOutputListToken.push_back(Token(KEYWORD,		"\"name\"",		4));
	expectedOutputListToken.push_back(Token(COLON,			":",			4));
	expectedOutputListToken.push_back(Token(TEXT,			"\"INPUT A\"",	4));
	expectedOutputListToken.push_back(Token(COMMA,			",",			4));

	expectedOutputListToken.push_back(Token(KEYWORD,		"\"wave\"",		5));
	expectedOutputListToken.push_back(Token(COLON,			":",			5));
	expectedOutputListToken.push_back(Token(TEXT,			"\"l..h.\"",	5));

	expectedOutputListToken.push_back(Token(RIGHTCURLY,		"}",			6));
	expectedOutputListToken.push_back(Token(COMMA,			",",			6));


	expectedOutputListToken.push_back(Token(LEFTCURLY,		"{",			7));

	expectedOutputListToken.push_back(Token(KEYWORD,		"\"name\"",		8));
	expectedOutputListToken.push_back(Token(COLON,			":",			8));
	expectedOutputListToken.push_back(Token(TEXT,			"\"INPUT B\"",	8));
	expectedOutputListToken.push_back(Token(COMMA,			",",			8));

	expectedOutputListToken.push_back(Token(KEYWORD,		"\"wave\"",		9));
	expectedOutputListToken.push_back(Token(COLON,			":",			9));
	expectedOutputListToken.push_back(Token(TEXT,			"\"l..h.\"",	9));

	expectedOutputListToken.push_back(Token(RIGHTCURLY,		"}",			10));
	expectedOutputListToken.push_back(Token(COMMA,			",",			10));


	expectedOutputListToken.push_back(Token(LEFTCURLY,		"{",			11));

	expectedOutputListToken.push_back(Token(COMMENT,		"//\"name\": \"INPUT C\",",		12));

	expectedOutputListToken.push_back(Token(KEYWORD,		"\"name\"",		13));
	expectedOutputListToken.push_back(Token(COLON,			":",			13));
	expectedOutputListToken.push_back(Token(TEXT,			"\"INPUT D\"",	13));
	expectedOutputListToken.push_back(Token(COMMA,			",",			13));

	expectedOutputListToken.push_back(Token(KEYWORD,		"\"wave\"",		14));
	expectedOutputListToken.push_back(Token(COLON,			":",			14));
	expectedOutputListToken.push_back(Token(TEXT,			"\"l..h.\"",	14));

	expectedOutputListToken.push_back(Token(RIGHTCURLY,		"}",			15));
	expectedOutputListToken.push_back(Token(COMMA,			",",			15));

	expectedOutputListToken.push_back(Token(COMMENT,		"/*{\n      \"name\": \"INPUT E\",\n      \"wave\": \"l..h.\"\n    }*/", 19));
	/*
	expectedOutputListToken.push_back(Token(LEFTCOMMENT,	"/*",			16));
	expectedOutputListToken.push_back(Token(LEFTCURLY,		"{",			16));

	expectedOutputListToken.push_back(Token(KEYWORD,		"\"name\"",		17));
	expectedOutputListToken.push_back(Token(COLON,			":",			17));
	expectedOutputListToken.push_back(Token(TEXT,			"\"INPUT E\"",	17));
	expectedOutputListToken.push_back(Token(COMMA,			",",			17));

	expectedOutputListToken.push_back(Token(KEYWORD,		"\"wave\"",		18));
	expectedOutputListToken.push_back(Token(COLON,			":",			18));
	expectedOutputListToken.push_back(Token(TEXT,			"\"l..h.\"",	18));

	expectedOutputListToken.push_back(Token(RIGHTCURLY,		"}",			19));
	expectedOutputListToken.push_back(Token(RIGHTCOMMENT,	"*///",			19));*/


	expectedOutputListToken.push_back(Token(LEFTCURLY,		"{",			20));

	expectedOutputListToken.push_back(Token(KEYWORD,		"\'name\'",		21));
	expectedOutputListToken.push_back(Token(COLON,			":",			21));
	expectedOutputListToken.push_back(Token(TEXT,			"\'INPUT F\'",	21));
	expectedOutputListToken.push_back(Token(COMMA,			",",			21));

	expectedOutputListToken.push_back(Token(KEYWORD,		"\'wave\'",		22));
	expectedOutputListToken.push_back(Token(COLON,			":",			22));
	expectedOutputListToken.push_back(Token(TEXT,			"\'l..h.\'",	22));

	expectedOutputListToken.push_back(Token(RIGHTCURLY,		"}",			23));
	expectedOutputListToken.push_back(Token(COMMA,			",",			23));


	expectedOutputListToken.push_back(Token(LEFTCURLY,		"{",			24));

	expectedOutputListToken.push_back(Token(KEYWORD,		"name",			25));
	expectedOutputListToken.push_back(Token(COLON,			":",			25));
	expectedOutputListToken.push_back(Token(TEXT,			"\"INPUT G\"",	25));
	expectedOutputListToken.push_back(Token(COMMA,			",",			25));

	expectedOutputListToken.push_back(Token(KEYWORD,		"wave",			26));
	expectedOutputListToken.push_back(Token(COLON,			":",			26));
	expectedOutputListToken.push_back(Token(TEXT,			"\"l..h.\"",	26));

	expectedOutputListToken.push_back(Token(RIGHTCURLY,		"}",			27));

	expectedOutputListToken.push_back(Token(RIGHTSQUARE,	"]",			28));

	expectedOutputListToken.push_back(Token(RIGHTCURLY,		"}",			29));

	lexingInputStringDOT(inputString, outputListToken);

	//printInConsoleListToken("Print outputListToken:", outputListToken);
	//printInConsoleListToken("Print expectedOutputListToken:", expectedOutputListToken);
	//printDevMessage(inputString);
	/*
	if (listsOfTokenAreEqual(outputListToken, expectedOutputListToken))
		return false;
	else
		return true;*/

	//printDevMessage("outputListToken " + to_string(outputListToken.size()));
	//printDevMessage("expectedOutputListToken " + to_string(expectedOutputListToken.size()));

	unsigned int lineNumber;
	if ((lineNumber = listsOfTokenAreEqual(outputListToken, expectedOutputListToken)) != 0) {
		printErrorMessage("Lists of Token are different at line " + to_string(lineNumber));
		return true;
	}
	else
		return false;
}


	/// Toolbox.h ---------------------------------------------------------------------------------


	/// Parser.h ----------------------------------------------------------------------------------

bool unitTest_parserInputTokenListDOT() {
	list<Token> inputListToken;	

	inputListToken.push_back(Token(KEYWORD,			"digraph",		1));
	inputListToken.push_back(Token(SYMBOLE,			"test",			1));
	inputListToken.push_back(Token(LEFTCURLY,		"{",			1));

	inputListToken.push_back(Token(SYMBOLE,			"I1",			2));
	inputListToken.push_back(Token(LEFTSQUARE,		"[",			2));
	inputListToken.push_back(Token(KEYWORD,			"label",		2));
	inputListToken.push_back(Token(EQUAL,			"=",			2));
	inputListToken.push_back(Token(TEXT,			"\"INPUT A\"",	2));
	inputListToken.push_back(Token(RIGHTSQUARE,		"]",			2));
	inputListToken.push_back(Token(SEMICOLON,		";",			2));

	inputListToken.push_back(Token(SYMBOLE,			"I2",			3));
	inputListToken.push_back(Token(LEFTSQUARE,		"[",			3));
	inputListToken.push_back(Token(KEYWORD,			"label",		3));
	inputListToken.push_back(Token(EQUAL,			"=",			3));
	inputListToken.push_back(Token(TEXT,			"\"INPUT B\"",	3));
	inputListToken.push_back(Token(RIGHTSQUARE,		"]",			3));
	inputListToken.push_back(Token(SEMICOLON,		";",			3));

	inputListToken.push_back(Token(COMMENT,			"//I3 [label = \"INPUT C\"];", 4));

	inputListToken.push_back(Token(LEFTCOMMENT,		"/*",			5));
	inputListToken.push_back(Token(SYMBOLE,			"I4",			5));
	inputListToken.push_back(Token(LEFTSQUARE,		"[",			5));
	inputListToken.push_back(Token(KEYWORD,			"label",		5));
	inputListToken.push_back(Token(EQUAL,			"=",			5));
	inputListToken.push_back(Token(TEXT,			"\"INPUT D\"",	5));
	inputListToken.push_back(Token(RIGHTSQUARE,		"]",			5));
	inputListToken.push_back(Token(SEMICOLON,		";",			5));

	inputListToken.push_back(Token(SYMBOLE,			"I5",			6));
	inputListToken.push_back(Token(LEFTSQUARE,		"[",			6));
	inputListToken.push_back(Token(KEYWORD,			"label",		6));
	inputListToken.push_back(Token(EQUAL,			"=",			6));
	inputListToken.push_back(Token(TEXT,			"\"INPUT E\"",	6));
	inputListToken.push_back(Token(RIGHTSQUARE,		"]",			6));
	inputListToken.push_back(Token(SEMICOLON,		";",			6));
	inputListToken.push_back(Token(RIGHTCOMMENT,	"*/",			6));
		
	inputListToken.push_back(Token(COMMENT,			"#I6 [label = \"INPUT F\"];", 7));
	
	inputListToken.push_back(Token(SYMBOLE,			"GATE",			8));
	inputListToken.push_back(Token(LEFTSQUARE,		"[",			8));
	inputListToken.push_back(Token(KEYWORD,			"label",		8));
	inputListToken.push_back(Token(EQUAL,			"=",			8));
	inputListToken.push_back(Token(TEXT,			"\"AND2\"",		8));
	inputListToken.push_back(Token(KEYWORD,			"shape",		8));
	inputListToken.push_back(Token(EQUAL,			"=",			8));
	inputListToken.push_back(Token(KEYWORD,			"box",			8));
	inputListToken.push_back(Token(RIGHTSQUARE,		"]",			8));
	inputListToken.push_back(Token(SEMICOLON,		";",			8));

	inputListToken.push_back(Token(SYMBOLE,			"O",			9));
	inputListToken.push_back(Token(LEFTSQUARE,		"[",			9));
	inputListToken.push_back(Token(KEYWORD,			"label",		9));
	inputListToken.push_back(Token(EQUAL,			"=",			9));
	inputListToken.push_back(Token(TEXT,			"\"OUTPUT\"",	9));
	inputListToken.push_back(Token(RIGHTSQUARE,		"]",			9));
	inputListToken.push_back(Token(SEMICOLON,		";",			9));

	inputListToken.push_back(Token(SYMBOLE,			"I1",			10));
	inputListToken.push_back(Token(AFFECTATION,		"->",			10));
	inputListToken.push_back(Token(SYMBOLE,			"GATE",			10));
	inputListToken.push_back(Token(AFFECTATION,		"->",			10));
	inputListToken.push_back(Token(SYMBOLE,			"O",			10));
	inputListToken.push_back(Token(SEMICOLON,		";",			10));

	inputListToken.push_back(Token(SYMBOLE,			"I2",			11));
	inputListToken.push_back(Token(AFFECTATION,		"->",			11));
	inputListToken.push_back(Token(SYMBOLE,			"GATE",			11));
	inputListToken.push_back(Token(SEMICOLON,		";",			11));

	inputListToken.push_back(Token(RIGHTCURLY,		"}",			12));

	//lexingInputStringDOT(inputString, outputListToken);

	/*
	unsigned int lineNumber;
	if ((lineNumber = listsOfTokenAreEqual(outputListToken, inputListToken)) != 0) {
		printInfoMessage("Lists of Token are different at line " + to_string(lineNumber));
		return true;
	}
	else
		return false;*/

	return true;
}


bool unitTest_parserInputTokenListJSON() {
	list<Token> inputListToken;

	map<string, vector<LogicState>> expectedOutputGraph;
	map<string, vector<LogicState>> outputGraph;

	inputListToken.push_back(Token(LEFTCURLY,		"{",			1));

	inputListToken.push_back(Token(KEYWORD,			"\"signal\"",	2));
	inputListToken.push_back(Token(COLON,			":",			2));
	inputListToken.push_back(Token(LEFTSQUARE,		"[",			2));


	inputListToken.push_back(Token(LEFTCURLY,		"{",			3));

	inputListToken.push_back(Token(KEYWORD,			"\"name\"",		4));
	inputListToken.push_back(Token(COLON,			":",			4));
	inputListToken.push_back(Token(TEXT,			"\"INPUT A\"",	4));
	inputListToken.push_back(Token(COMMA,			",",			4));

	inputListToken.push_back(Token(KEYWORD,			"\"wave\"",		5));
	inputListToken.push_back(Token(COLON,			":",			5));
	inputListToken.push_back(Token(TEXT,			"\"l..h.\"",	5));

	inputListToken.push_back(Token(RIGHTCURLY,		"}",			6));
	inputListToken.push_back(Token(COMMA,			",",			6));


	inputListToken.push_back(Token(LEFTCURLY,		"{",			7));

	inputListToken.push_back(Token(KEYWORD,			"\"name\"",		8));
	inputListToken.push_back(Token(COLON,			":",			8));
	inputListToken.push_back(Token(TEXT,			"\"INPUT B\"",	8));
	inputListToken.push_back(Token(COMMA,			",",			8));

	inputListToken.push_back(Token(KEYWORD,			"\"wave\"",		9));
	inputListToken.push_back(Token(COLON,			":",			9));
	inputListToken.push_back(Token(TEXT,			"\"l..h.\"",	9));

	inputListToken.push_back(Token(RIGHTCURLY,		"}",			10));
	inputListToken.push_back(Token(COMMA,			",",			10));


	inputListToken.push_back(Token(LEFTCURLY,		"{",			11));

	inputListToken.push_back(Token(COMMENT,			"//\"name\": \"INPUT C\",",		12));

	inputListToken.push_back(Token(KEYWORD,			"\"name\"",		13));
	inputListToken.push_back(Token(COLON,			":",			13));
	inputListToken.push_back(Token(TEXT,			"\"INPUT D\"",	13));
	inputListToken.push_back(Token(COMMA,			",",			13));

	inputListToken.push_back(Token(KEYWORD,			"\"wave\"",		14));
	inputListToken.push_back(Token(COLON,			":",			14));
	inputListToken.push_back(Token(TEXT,			"\"l..h.\"",	14));

	inputListToken.push_back(Token(RIGHTCURLY,		"}",			15));
	inputListToken.push_back(Token(COMMA,			",",			15));

	inputListToken.push_back(Token(COMMENT,			"/*{\n      \"name\": \"INPUT E\",\n      \"wave\": \"l..h.\"\n    }*/", 19));
	/*
	inputListToken.push_back(Token(LEFTCOMMENT,		"/*",			16));
	inputListToken.push_back(Token(LEFTCURLY,		"{",			16));

	inputListToken.push_back(Token(KEYWORD,			"\"name\"",		17));
	inputListToken.push_back(Token(COLON,			":",			17));
	inputListToken.push_back(Token(TEXT,			"\"INPUT E\"",	17));
	inputListToken.push_back(Token(COMMA,			",",			17));

	inputListToken.push_back(Token(KEYWORD,			"\"wave\"",		18));
	inputListToken.push_back(Token(COLON,			":",			18));
	inputListToken.push_back(Token(TEXT,			"\"l..h.\"",	18));

	inputListToken.push_back(Token(RIGHTCURLY,		"}",			19));
	inputListToken.push_back(Token(RIGHTCOMMENT,	"*///",			19));


	inputListToken.push_back(Token(LEFTCURLY,		"{",			20));

	inputListToken.push_back(Token(KEYWORD,			"\'name\'",		21));
	inputListToken.push_back(Token(COLON,			":",			21));
	inputListToken.push_back(Token(TEXT,			"\'INPUT F\'",	21));
	inputListToken.push_back(Token(COMMA,			",",			21));

	inputListToken.push_back(Token(KEYWORD,			"\'wave\'",		22));
	inputListToken.push_back(Token(COLON,			":",			22));
	inputListToken.push_back(Token(TEXT,			"\'l..h.\'",	22));

	inputListToken.push_back(Token(RIGHTCURLY,		"}",			23));
	inputListToken.push_back(Token(COMMA,			",",			23));


	inputListToken.push_back(Token(LEFTCURLY,		"{",			24));

	inputListToken.push_back(Token(KEYWORD,			"name",			25));
	inputListToken.push_back(Token(COLON,			":",			25));
	inputListToken.push_back(Token(TEXT,			"\"INPUT G\"",	25));
	inputListToken.push_back(Token(COMMA,			",",			25));

	inputListToken.push_back(Token(KEYWORD,			"wave",			26));
	inputListToken.push_back(Token(COLON,			":",			26));
	inputListToken.push_back(Token(TEXT,			"\"l..h.\"",	26));

	inputListToken.push_back(Token(RIGHTCURLY,		"}",			27));

	inputListToken.push_back(Token(RIGHTSQUARE,		"]",			28));

	inputListToken.push_back(Token(RIGHTCURLY,		"}",			29));

	parserInputTokenListJSON(inputListToken, outputGraph);

	//printInConsoleMapWave("Print outputGraph:", outputGraph);

	vector<LogicState> tempVector;

	tempVector.push_back(X);
	tempVector.push_back(L);
	tempVector.push_back(L);
	tempVector.push_back(L);
	tempVector.push_back(H);
	tempVector.push_back(H);
	expectedOutputGraph.insert(pair<string, vector<LogicState>>("INPUT A", tempVector));
	expectedOutputGraph.insert(pair<string, vector<LogicState>>("INPUT B", tempVector));
	expectedOutputGraph.insert(pair<string, vector<LogicState>>("INPUT D", tempVector));
	expectedOutputGraph.insert(pair<string, vector<LogicState>>("INPUT F", tempVector));
	expectedOutputGraph.insert(pair<string, vector<LogicState>>("INPUT G", tempVector));

	if (expectedOutputGraph != outputGraph) {
		printInfoMessage("Output graphs are different");
		return true;
	}
	else
		return false;
	return true;
}

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

	if (unitTest_lexingInputStringJSON()) { printErrorMessage("Error during the test of \"unitTest_lexingInputStringJSON()\""); errorNumber++; }
	else printInfoMessage("OK with the test of \"unitTest_lexingInputStringJSON()\"");

	if (unitTest_parserInputTokenListDOT()) { printErrorMessage("Error during the test of \"unitTest_parserInputTokenListDOT()\""); errorNumber++; }
	else printInfoMessage("OK with the test of \"unitTest_parserInputTokenListDOT()\"");

	if (unitTest_parserInputTokenListJSON()) { printErrorMessage("Error during the test of \"unitTest_parserInputTokenListJSON()\""); errorNumber++; }
	else printInfoMessage("OK with the test of \"unitTest_parserInputTokenListJSON()\"");		

	printInfoMessage("Unit test(s) ended with " + to_string(errorNumber) + " error(s)");
}


#endif