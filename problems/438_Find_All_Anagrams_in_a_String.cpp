//
// Created by user on 2025/8/29.
//

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ans;

        if(p.size() > s.size()){
            return ans;
        }

        int len = p.size();

        vector<int> original = vector(26, 0);
        vector<int> anagrams = vector(26, 0);

        for (int i = 0; i < p.size(); ++i) {
            original[p[i]-'a']++;
            anagrams[s[i]-'a']++;
        }

        for (int i = len; i < s.size(); ++i) {
            if(original == anagrams){
                ans.push_back(i-len);
            }
            anagrams[s[i-len]-'a']--;
            anagrams[s[i]-'a']++;
        }

        if(original == anagrams){
            ans.push_back(s.size()-len);
        }

        return ans;
    }
};