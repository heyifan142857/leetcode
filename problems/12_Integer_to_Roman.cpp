//
// Created by user on 2025/10/20.
//
#include <string>
#include <vector>

using namespace std;

class Solution {
    vector<pair<int, string>> romans = {
            {1000, "M"},
            {500,  "D"},
            {100,  "C"},
            {50,   "L"},
            {10,   "X"},
            {5,    "V"},
            {1,    "I"}
    };
public:
    string intToRoman(int num) {
        if (num <= 0) {
            return "";
        }

        int start = num;
        while (start / 10) {
            start /= 10;
        }

        if (start == 4) {
            if (400 <= num) {
                return "CD" + intToRoman(num - 400);
            }
            if (40 <= num) {
                return "XL" + intToRoman(num - 40);
            }
            if (4 <= num) {
                return "IV" + intToRoman(num - 4);
            }
        } else if (start == 9) {
            if (900 <= num) {
                return "CM" + intToRoman(num - 900);
            }
            if (90 <= num) {
                return "XC" + intToRoman(num - 90);
            }
            if (9 <= num) {
                return "IX" + intToRoman(num - 9);
            }
        } else {
            for (auto roman: romans) {
                if (roman.first <= num) {
                    return roman.second + intToRoman(num - roman.first);
                }
            }
        }
        return "";
    }
};
