// 1021. Remove Outermost Parentheses
// Created automatically
// Created at 2026-10-08 10:46:11

#include <string>
using namespace std;

class Solution {
public:
    string removeOuterParentheses(string s) {
        int count = 0;
        string res;
        for (const auto ch : s) {
            if (ch == '(') {
                count++;
                if (count > 1) {
                    res += ch;
                }
            } else {
                count--;
                if (count > 0) {
                    res += ch;
                }
            }
        }
        return res;
    }
};
