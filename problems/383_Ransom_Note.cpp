// 383. Ransom Note
// Created automatically
// Created at 2026-03-05 14:25:33

#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> charCount(26, 0);
        for (char c : magazine) {
            charCount[c - 'a']++;
        }
        for (char c : ransomNote) {
            if (--charCount[c - 'a'] < 0) {
                return false;
            }
        }
        return true;
    }
};