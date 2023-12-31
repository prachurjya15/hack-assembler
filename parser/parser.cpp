#include "parser.h"

#include "../utils/utils.h"


const char i_Ainstruction = '@';
const char i_Linstruction = '(';

Parser::Parser(string filename): m_filename(filename){
    // Open the file and store in a member variable.
    m_fileReaderPtr.open(filename);
}

bool Parser::hasMoreLines() {
    // cout << "hasMoreLines" << '\n';
    return !m_fileReaderPtr.eof();
}

bool Parser::checkValidInstruction(string instruction) {
    // If WhiteSpace return false;
    if (instruction.length() == 0) {
        return false;
    }
    // if starts with // return false;
    for(int i=0;i<instruction.length();i++) {
        if(instruction[i] && instruction[i]!= '/') {
             return true;
        } 
    }
    return false;
}

string Parser::getNextInstruction() {
    // cout << "getNextInstruction" << '\n';
    string nextInstruction;
    bool isValidInstruction = false;
    // while(!isValidInstruction) {
        getline(m_fileReaderPtr, nextInstruction);
        isValidInstruction = checkValidInstruction(nextInstruction);
    // }
   
    m_currInstruction = nextInstruction;
    this->instructionType();
    return nextInstruction;
}

INSTRUCTION_TYPE Parser::instructionType(){
    // If string starts with @ --> A Instruction
    // If string starts with (  --> L Instruction
    // else  --> C Instruction
    // cout << "Instruction Type" << '\n';
    if(m_currInstruction[0] == i_Ainstruction) {
        m_currInstructionType = INSTRUCTION_TYPE::A_INSTRUCTION;
        return INSTRUCTION_TYPE::A_INSTRUCTION;
    } else if(m_currInstruction[1] == i_Linstruction) {
         m_currInstructionType = INSTRUCTION_TYPE::L_INSTRUCTION;
        return INSTRUCTION_TYPE::L_INSTRUCTION;
    } else {
         m_currInstructionType = INSTRUCTION_TYPE::C_INSTRUCTION;
        return INSTRUCTION_TYPE::C_INSTRUCTION;
    }
}

string Parser::symbol() {
    switch (m_currInstructionType)
    {
    case INSTRUCTION_TYPE::A_INSTRUCTION:
        return  Utils::RemoveWhitespaces(m_currInstruction.substr(1));
        break;
    case INSTRUCTION_TYPE::L_INSTRUCTION:
        return Utils::RemoveWhitespaces(m_currInstruction.substr(1, m_currInstruction.length()-2));
        break;
    default:
        return "";
        break;
    }   
}

string Parser::dest() {
    int equalPos = m_currInstruction.find("=");
    return m_currInstruction.substr(0, equalPos).length() > 0 ? Utils::RemoveWhitespaces(m_currInstruction.substr(0, equalPos)) : "null";
}

string Parser::comp() {
    int equalPos = m_currInstruction.find("=");
    int semiColonPos = m_currInstruction.find(";");
    if ( semiColonPos == string::npos && equalPos >= 0) {
        return m_currInstruction.substr(equalPos+1).length() > 0 ? Utils::RemoveWhitespaces(m_currInstruction.substr(equalPos+1)) :"null";
    }
    return m_currInstruction.substr(equalPos+1, semiColonPos - equalPos - 1).length()> 0 ? Utils::RemoveWhitespaces(m_currInstruction.substr(equalPos+1, semiColonPos - equalPos - 1)) : "null" ;
}

string Parser::jump() {
    // TODO : Handle Comments
    int semiColonPos = m_currInstruction.find(";");
    if ( semiColonPos == string::npos) {
        return "null";
    }
    return Utils::RemoveWhitespaces(m_currInstruction.substr(semiColonPos+1));
}

// Test code
// int main() {
//     string file = "Add.asm";
//     Parser* p = new Parser(file);
//     while(p->hasMoreLines()){
//         p->getNextInstruction();
//         // cout << p->symbol() << '\n';
//         if (p->instructionType() == INSTRUCTION_TYPE::C_INSTRUCTION) {
//             cout << p->comp()<< "<-- COMP" <<'\n';
//             cout << p->dest()<< "<-- DEST" << '\n';
//         } 
        
//     }
//     delete p;
// }