// 856. Score of Parentheses
// Created automatically
// Created at 2026-10-05 22:39:02

#include <string>
using namespace std;

class Solution {
public:
    int scoreOfParentheses(string s) {
        int sum = 0;
        int multiplier = 1;

        bool flag = false;
        for (const char c : s) {
            if (c == '(') {
                flag = true;
                multiplier *= 2;
            } else {
                if (flag == true) {
                    sum += multiplier;
                }
                flag = false;
                multiplier /= 2;
            }
        }
        return sum / 2;
    }
};
