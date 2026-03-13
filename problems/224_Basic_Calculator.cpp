// 224. Basic Calculator
// Created automatically
// Created at 2026-03-13 16:32:30

#include <bits/stdc++.h>
using namespace std;

class Solution {
    // produce tokenized RPN as a vector of strings (numbers and operators)
    vector<string> toRPN(const string &s) {
        vector<string> output;
        stack<char> ops;
        auto precedence = [&](char op){
            if (op == '+' || op == '-') return 1;
            if (op == '*' || op == '/') return 2;
            return 0;
        };

        int n = s.size();
        bool expectUnary = true; // at start we can have a unary +/-, or after '('
        for (int i = 0; i < n; ) {
            char c = s[i];
            if (isspace(c)) { i++; continue; }
            if (isdigit(c)) {
                int j = i;
                while (j < n && isdigit(s[j])) j++;
                output.push_back(s.substr(i, j - i));
                i = j;
                expectUnary = false;
            } else if (c == '(') {
                ops.push(c);
                i++;
                expectUnary = true;
            } else if (c == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    output.push_back(string(1, ops.top()));
                    ops.pop();
                }
                if (!ops.empty()) ops.pop();
                i++;
                expectUnary = false;
            } else if (c == '+' || c == '-' || c == '*' || c == '/') {
                if ((c == '+' || c == '-') && expectUnary) {
                    // unary plus/minus: treat as 0 <op> number, push a zero first
                    output.push_back("0");
                }
                while (!ops.empty() && ops.top() != '(' && precedence(ops.top()) >= precedence(c)) {
                    output.push_back(string(1, ops.top()));
                    ops.pop();
                }
                ops.push(c);
                i++;
                expectUnary = true;
            } else {
                // unknown char, skip
                i++;
            }
        }
        while (!ops.empty()) {
            output.push_back(string(1, ops.top()));
            ops.pop();
        }
        return output;
    }
public:
    int calculate(string s) {
        vector<string> rpn = toRPN(s);
        stack<long long> st;
        for (const string &tok : rpn) {
            if (!tok.empty() && (isdigit(tok[0]) || (tok.size() > 1 && tok[0] == '-' && isdigit(tok[1])))) {
                st.push(stoll(tok));
            } else if (tok.size() == 1) {
                char c = tok[0];
                long long b = st.top(); st.pop();
                long long a = st.top(); st.pop();
                if (c == '+') st.push(a + b);
                else if (c == '-') st.push(a - b);
                else if (c == '*') st.push(a * b);
                else if (c == '/') st.push(a / b);
            }
        }
        long long ans = st.empty() ? 0 : st.top();
        return static_cast<int>(ans);
    }
};