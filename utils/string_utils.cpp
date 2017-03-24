//
// Created by Admin on 3/21/2017.
//

#include <cctype>
#include <cstring>
#include <string>
#include "string_utils.h"

string trim(string &str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
