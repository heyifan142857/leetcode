//
// Created by user on 2025/9/15.
//
#include <string>
#include <unordered_set>
#include <sstream>
using namespace std;

class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        int cnt = 0;
        unordered_set<char> brokenSet;
        for (auto c:brokenLetters) {
            brokenSet.insert(c);
        }

        stringstream sentence(text);
        string word;

        while (sentence >> word){
            bool canType = true;
            for (auto c: word) {
                if(brokenSet.contains(c)){
                    canType = false;
                    break;
                }
            }
            if(canType){
                cnt++;
            }
        }
        return cnt;
    }
};