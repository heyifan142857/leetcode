// 71. Simplify Path
// Created automatically
// Created at 2026-03-13 16:03:47

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        string result;
        vector<string> stack;
        stringstream ss(path);
        string token;
        while (getline(ss, token, '/')) {
            if (token.empty() || token == ".") {
                continue;
            } else if (token == "..") {
                if (!stack.empty()) {
                    stack.pop_back();   
                }
            } else {
                stack.push_back(token);
            }
        }
        for (const auto& dir : stack) {
            result += "/" + dir;
        }
        return result.empty() ? "/" : result;
    }
};