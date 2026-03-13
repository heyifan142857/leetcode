// 150. Evaluate Reverse Polish Notation
// Created automatically
// Created at 2026-03-13 16:22:18

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> s;
        for (const auto& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int b = s.top(); s.pop();
                int a = s.top(); s.pop();
                if (token == "+") {
                    s.push(a + b);
                } else if (token == "-") {
                    s.push(a - b);
                } else if (token == "*") {
                    s.push(a * b);
                } else {
                    s.push(a / b);
                }
            } else {
                s.push(stoi(token));
            }
        }
        return s.top();        
    }
};