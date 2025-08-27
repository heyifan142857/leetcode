//
// Created by user on 2025/8/27.
//

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagrams;
        for (auto str: strs) {
            string sorted_str = str;
            sort(sorted_str.begin(), sorted_str.end());
            anagrams[sorted_str].push_back(str);
        }

        vector<vector<string>> result;
        for (auto& [key, group] : anagrams) {
            result.push_back(group);
        }
        return result;
    }
};