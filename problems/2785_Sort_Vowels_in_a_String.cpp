//
// Created by user on 2025/9/11.
//
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;


class Solution {
public:
    string sortVowels(string s) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        vector<int> order;
        vector<int> vs;
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            if(vowels.contains(c)){
                vs.push_back(c);
                order.push_back(i);
            }
        }
        sort(vs.begin(), vs.end());
        for (int i = 0; i < order.size(); ++i) {
            s[order[i]] = vs[i];
        }
        return s;
    }
};