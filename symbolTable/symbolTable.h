#include <iostream>
#include <unordered_map>


using namespace std;

#ifndef SYMBOLTAB_H
#define SYMBOLTB_H

class SymbolTable{
    public:
        SymbolTable();
        void AddEntry(string symbol, int address);
        bool Contains(string symbol);
        int  GetAddress(string symbol);
    private:
        unordered_map<string, int> m_symbolMap;
};

#endif