//
// Created by user on 2025/9/14.
//
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
using namespace std;

class Solution {
public:
    string devowel(string s) {
        for (auto &c : s) {
            if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u')
                c = '*';
        }
        return s;
    }

    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_set<string> exact(wordlist.begin(), wordlist.end());
        unordered_map<string, string> caseInsensitive;
        unordered_map<string, string> vowelInsensitive;

        for (auto &w : wordlist) {
            string lower = w;
            for (auto &c : lower) c = tolower(c);

            if (!caseInsensitive.count(lower)) {
                caseInsensitive[lower] = w;
            }

            string dev = devowel(lower);
            if (!vowelInsensitive.count(dev)) {
                vowelInsensitive[dev] = w;
            }
        }

        vector<string> ans;
        for (auto q : queries) {
            if (exact.count(q)) {
                ans.push_back(q);
                continue;
            }

            string lower = q;
            for (auto &c : lower) c = tolower(c);

            if (caseInsensitive.count(lower)) {
                ans.push_back(caseInsensitive[lower]);
                continue;
            }

            string dev = devowel(lower);
            if (vowelInsensitive.count(dev)) {
                ans.push_back(vowelInsensitive[dev]);
                continue;
            }

            ans.push_back("");
        }
        return ans;
    }
};
