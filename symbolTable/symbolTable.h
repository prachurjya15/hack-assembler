#include <iostream>
#include <unordered_map>


using namespace std;

#ifndef SYMBOLTAB_H
#define SYMBOLTB_H

class SymbolTable{
    public:
        void AddEntry(string symbol, string address);
        bool Contains(string symbol);
        int  GetAddress(string symbol);
    private:
        unordered_map<string, string> m_symbolMap;
};

#endif