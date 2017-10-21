//
// Created by Admin on 3/21/2017.
//

#include <cctype>
#include <string>
#include "string_utils.hpp"

string trim(string &str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

vector<string> *splitOver(string str, char c) {
    int idx = 0;
    vector<string> *tokens = new vector<string>();
    while(idx < str.size()){
        string s = "";
        while(idx < str.size() && str[idx] != c){
            s += str[idx];
            if(str[idx] == '\\' && idx+1 < str.size()){
                idx++;
                s += str[idx];
            }
            idx++;
        }
        if(s.size())
            tokens->push_back(s);
        idx++;
    }
    return tokens;
}
