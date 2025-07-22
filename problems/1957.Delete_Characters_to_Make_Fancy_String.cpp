//
// Created by user on 2025/7/22.
//
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string makeFancyString(string s) {
        vector<char> str;
        char previous = ' ';
        int count = 0;
        for (char c:s) {
            if(c == previous){
                count++;
                if(count < 3){
                    str.push_back(c);
                }
            }else{
                count = 1;
                previous = c;
                str.push_back(c);
            }
        }
        string ans(str.begin(), str.end());
        return ans;
    }
};

/*
官方题解

方法一：模拟
class Solution {
public:
    string makeFancyString(string s) {
        string res;   // 删除后的字符串
        // 遍历 s 模拟删除过程
        for (char ch : s){
            int n = res.size();
            if (n >= 2 && res[n-1] == ch && res[n-2] == ch){
                // 如果 res 最后两个字符与当前字符均相等，则不添加
                continue;
            }
            // 反之则添加
            res.push_back(ch);
        }
        return res;
    }
};
*/