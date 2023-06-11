#include <string.h>
#include <iostream>

using namespace std;

#ifndef UTILS_H

#define UTLS_H
class Utils{
    public:
        static string convertToBinary(int num);
        static string RemoveWhitespaces(const string& input);
};


#endif