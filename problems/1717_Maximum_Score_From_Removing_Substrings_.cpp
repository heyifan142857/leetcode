//
// Created by user on 2025/7/23.
//
#include <string>
using namespace std;

class Solution {
public:
    int maximumGain(string s, int x, int y) {
        if (x < y) {
            swap(x, y);
            for (char& c : s) {
                if (c == 'a') c = 'b';
                else if (c == 'b') c = 'a';
            }
        }

        int res = 0;
        string tmp;

        for (char c : s) {
            if (!tmp.empty() && tmp.back() == 'a' && c == 'b') {
                tmp.pop_back();
                res += x;
            } else {
                tmp.push_back(c);
            }
        }

        string rest;
        for (char c : tmp) {
            if (!rest.empty() && rest.back() == 'b' && c == 'a') {
                rest.pop_back();
                res += y;
            } else {
                rest.push_back(c);
            }
        }

        return res;
    }
};