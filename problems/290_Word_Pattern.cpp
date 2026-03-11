// 290. Word Pattern
// Created automatically
// Created at 2026-03-11 14:16:32
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        unordered_map<char, string> charToWord;
        unordered_map<string, char> wordToChar;
        vector<string> words;
        string word;
        for (char ch : s) {
            if (ch == ' ') {
                if (!word.empty()) {
                    words.push_back(word);
                    word = "";
                }
            } else {
                word += ch;
            }
        }
        if (!word.empty()) {
            words.push_back(word);
        }
        
        if (pattern.size() != words.size()) return false;
        
        for (int k = 0; k < pattern.size(); ++k) {
            char c = pattern[k];
            string w = words[k];
            if (charToWord.count(c)) {
                if (charToWord[c] != w) return false;
            } else {
                charToWord[c] = w;
            }
            if (wordToChar.count(w)) {
                if (wordToChar[w] != c) return false;
            } else {
                wordToChar[w] = c;
            }
        }
        return true;
    }
};
