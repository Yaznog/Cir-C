#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

using namespace std;

enum TokenType {
    LEFTPARENTHESIS,    // (
    RIGHTPARENTHESIS,   // )
    LEFTSQUARE,         // [
    RIGHTSQUARE,        // ]
    LEFTCURLY,          // {
    RIGHTCURLY,         // }
    COMMA,              // ,
    COLON,              // :
    SEMICOLON,          // ;
    TEXT,               // "text"
    COMMENT,            // //
    EQUAL,              // =
    AFFECTATION,        // ->
    SYMBOLE,            // other
    UNKNOWN,            // unknown
    HASH,               // #
    LEFTCOMMENT,        // /*
    RIGHTCOMMENT,       // */
    KEYWORD,             // (DOT) digraph, label, shape || (JSON) signal, name, wave, data
    SLASH
};

const string keywordArrayDOT[4] = { "digraph", "label", "shape", "box" };
const string keywordArrayJSON[13] = { "signal", "name", "wave", "data", "phase", "period", "node", "head", "text", "class", "foot", "config", "edge" };

class Token {

public:

    Token(TokenType inputType = UNKNOWN, const string& inputValue = "void", unsigned int inputLine = 0) : m_type(inputType), m_value(inputValue), m_line(inputLine) {};

    
    static string getStringType(const string& inputString) {
        return "nope";
    };

    string toString() { return this->convertTokenTypeToString(this->m_type) + " " + this->m_value + " " + to_string(this->m_line); };

    inline const TokenType getType() { return this->m_type; };
    inline const string getTypeString() { return this->convertTokenTypeToString(this->m_type); };
    inline const string getValue() { return this->m_value; };
    inline const unsigned int getLine() { return this->m_line; };

    inline void setType(TokenType inputType) { this->m_type = inputType; };
    inline void setValue(string inputValue) { this->m_value = inputValue; };
    inline void setLine(unsigned int inputLine) { this->m_line = inputLine; };

    string convertTokenTypeToString(TokenType inputTokenType) {
        switch (inputTokenType) {
        case 0:
            return "LEFTPARENTHESIS";
        case 1:
            return "RIGHTPARENTHESIS";
        case 2:
            return "LEFTSQUARE";
        case 3:
            return "RIGHTSQUARE";
        case 4:
            return "LEFTCURLY";
        case 5:
            return "RIGHTCURLY";
        case 6:
            return "COMMA";
        case 7:
            return "COLON";
        case 8:
            return "SEMICOLON";
        case 9:
            return "TEXT";
        case 10:
            return "COMMENT";
        case 11:
            return "EQUAL";
        case 12:
            return "AFFECTATION";
        case 13:
            return "SYMBOLE";
        case 14:
            return "UNKNOWN";
        case 15:
            return "HASH";
        case 16:
            return "LEFTCOMMENT";
        case 17:
            return "RIGHTCOMMENT";
        case 18:
            return "KEYWORD";
        case 19:
            return "SLASH";
        }
        return "UNKNOWN";
    }
    
    bool operator==(Token& other) {
        if (m_type == other.m_type && m_value == other.m_value && m_line == other.m_line)
            return true;
        else
            return false;
    }
    
    bool operator!=(Token& other) {
        if (m_type != other.m_type || m_value != other.m_value || m_line != other.m_line)
            return true;
        else
            return false;
    }

    bool operator&(Token& other) {
        if (m_type != other.m_type || m_value != other.m_value || m_line != other.m_line)
            return true;
        else
            return false;
    }

private:

    TokenType m_type;
    string m_value;
    unsigned int m_line;
    
};

#endif