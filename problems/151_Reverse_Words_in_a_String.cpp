//
// Created by azote on 11/18/25.
//
#include <string>
#include <sstream>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        istringstream iss(s);
        string word;
        string res = "";

        while (iss >> word) {
            if (res.empty()) {
                res = word;
            } else {
                res = word + " " + res;
            }
        }
        return res;
    }
};
