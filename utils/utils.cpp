#include <bitset>

#include "utils.h"

string Utils::convertToBinary(int num) {
    std::bitset<16> binary(num);
    return binary.to_string();
}

string Utils::RemoveWhitespaces(const string& input) {
    string result;
    for (char c : input) {
        if (!isspace(c)) {
            result += c;
        }
    }
    return result;
}