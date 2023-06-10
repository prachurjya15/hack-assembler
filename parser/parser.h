#include <iostream>
#include <fstream>
#include <string.h>

#ifndef PARSER_H
#define PARSER_H


using namespace std;

enum class INSTRUCTION_TYPE {
            A_INSTRUCTION,
            C_INSTRUCTION,
            L_INSTRUCTION
        };


class Parser {
    public:
        Parser(string filename);
        bool hasMoreLines();
        string getNextInstruction();
        INSTRUCTION_TYPE instructionType();
        string symbol();
        string dest();
        string comp();
        string jump();
    private:
        string m_filename;
        fstream m_fileReaderPtr; 
        string m_currInstruction;
        INSTRUCTION_TYPE m_currInstructionType;       
};

#endif