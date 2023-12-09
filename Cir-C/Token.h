#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

using namespace std;

class Token {

public:
    /*
    Token(const string& inputType, const string& inputValue, unsigned int inputLine) {
        this.type = inputType;
        this.value = inputValue;
        this.line = inputLine;
    }*/

    Token(const string& inputType = "void", const string& inputValue = "void", unsigned int inputLine = 0) : m_type(inputType), m_value(inputValue), m_line(inputLine) {};

    
    static string getStringType(const string& inputString) {
        return "nope";
    };

    string toString() { return this->m_type + " " + this->m_value + " " + to_string(this->m_line); };

    inline const string getType() { return this->m_type; };
    inline const string getValue() { return this->m_value; };
    inline const unsigned int getLine() { return this->m_line; };

    inline void setType(string inputType) { this->m_type = inputType; };
    inline void setValue(string inputValue) { this->m_value = inputValue; };
    inline void setLine(unsigned int inputLine) { this->m_line = inputLine; };
    
    bool operator==(Token& other) {
        if (m_type == other.m_type && m_value == other.m_value && m_line == other.m_line)
            return true;
        else
            return false;
    }

private:

    string m_type;
    string m_value;
    unsigned int m_line;

    
};

#endif