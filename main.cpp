#include <iostream>
#include <fstream>
#include <string.h>

#include "utils/utils.h"
#include "parser/parser.h"
#include "symbolTable/symbolTable.h"
#include "genCode/genCode.h"

void GenerateSymbolTable(string fileName = "Add.asm") {
    Parser* p = new Parser(fileName);
    SymbolTable* symTbl = new SymbolTable();
    
    int lineNum = 0;
    int currMemAddr = 16;

    while(p->hasMoreLines()) {
        string instruction = p->getNextInstruction();
        if(p->instructionType() == INSTRUCTION_TYPE::A_INSTRUCTION ) {
            string currSymbol = p->symbol();
            int digCount = 0;
            for(int i=0;i<currSymbol.length();i++){
                if(isdigit(currSymbol[i])){
                    digCount++;
                }
            }
            if(digCount == currSymbol.length() ){
                continue;
            }
            if (!symTbl->Contains(currSymbol)) {
                symTbl->AddEntry(currSymbol, currMemAddr);
                currMemAddr++;
            }
        }
        if(p->instructionType() == INSTRUCTION_TYPE::L_INSTRUCTION) {
            string symbol =  p->symbol();
            symTbl->AddEntry(symbol, lineNum+1);
            continue; 
        }
        lineNum++;
    }

    delete p;
    delete symTbl;
}

void DecodeAndWriteToFile(string srcFileName="Add.asm") {
    // TODO: Write to /output folder
    int dotPos = srcFileName.find(".");
    string outFileName = "output/" + srcFileName.substr(0, dotPos+1) + "hack";
    ofstream outStrm;
    outStrm.open(outFileName, ios::app);

    Parser* p = new Parser(srcFileName);
    SymbolTable* symTbl = new SymbolTable();
    GenCode* genCode = new GenCode();

    while(p->hasMoreLines()) {
        string instruction = p->getNextInstruction();
        if (p->instructionType() == INSTRUCTION_TYPE::A_INSTRUCTION ){
            string symbol = p->symbol();
            // TODO :If it is non-variable i.e. @10 etc. directly convert
            string binaryNum;
            if(symTbl->Contains(symbol)) {
                 int addr = symTbl->GetAddress(symbol);
                 binaryNum = Utils::convertToBinary(addr);
            } else {
                int numAddr = atoi(symbol.c_str());
                binaryNum = Utils::convertToBinary(numAddr);
            }
            outStrm << binaryNum << '\n';
        }
        if(p->instructionType() == INSTRUCTION_TYPE::C_INSTRUCTION) {
             string binStr = "111";
             string comp = p->comp();
             string dest = p->dest();
             string jump = p->jump();
             cout << "COMP" << " "<< comp << '\n';
             cout << "len" << "  "<< comp.length() << '\n';
            //  cout << genCode->Comp(comp) << " " << genCode->Dest(dest) << " "<< genCode->Jump(jump) << '\n';
            string genComp = genCode->Comp(comp);
            string genDest = genCode->Dest(dest);
            string genJump = genCode ->Jump(jump);

            outStrm << "111" << genComp << genDest<< genJump << '\n';
        }
    }
    
    delete p;
    delete symTbl;
    delete genCode;   
}

int main() {
    // Get the Input file name from the arguments
    // 1st parse Generate the symbol Table
    GenerateSymbolTable();
    // 2nd parse Decode everything and write to File
    DecodeAndWriteToFile();
}