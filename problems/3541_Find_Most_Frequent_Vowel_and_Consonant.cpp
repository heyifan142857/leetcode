//
// Created by user on 2025/9/13.
//
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int maxFreqSum(string s) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        vector<int> letters(26, 0);
        for (auto c: s) {
            letters[(int)(c-'a')]++;
        }
        int max1 = 0;
        int max2 = 0;
        for (int i = 0; i < letters.size(); ++i) {
            if(vowels.contains('a'+i)){
                continue;
            }
            max1 = max(max1, letters[i]);
        }
        for (auto v: vowels) {
            max2 = max(max2, letters[(int)(v-'a')]);
        }
        return max1+max2;
    }
};