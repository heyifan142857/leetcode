//
// Created by user on 2025/9/16.
//
#include <string>
#include <stack>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> parentheses;
        unordered_set<char> left = {'(', '[', '{'};
        for (auto c: s) {
            if(left.contains(c)){
                parentheses.push(c);
            }else if(parentheses.empty()){
                return false;
            }else{
                char top = parentheses.top();
                if((top == '(' && c == ')') || (top == '[' && c == ']') || (top == '{' && c == '}')){
                    parentheses.pop();
                    continue;
                }else{
                    return false;
                }
            }
        }
        if(parentheses.empty()){
            return true;
        }else{
            return false;
        }
    }
};