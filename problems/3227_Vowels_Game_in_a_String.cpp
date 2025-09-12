//
// Created by user on 2025/9/12.
//
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool doesAliceWin(string s) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        for (auto c: s) {
            if(vowels.contains(c)){
                return true;
            }
        }
        return false;
    }
};