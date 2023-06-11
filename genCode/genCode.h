#include <iostream>
#include <fstream>
#include <string.h>
#include <unordered_map>

using namespace std;

#ifndef GENCODE_H
#define GENCODE_H

class GenCode {
    public:
        GenCode();
        string Dest(string instruction);
        string Comp(string instruction);
        string Jump(string instruction);
    private:
        void fillDestMap();
        void fillCompMap();
        void fillJumpMap();
        unordered_map<string, string> m_destMap;
        unordered_map<string, string> m_compMap;
        unordered_map<string, string> m_jumpMap;
};

#endif