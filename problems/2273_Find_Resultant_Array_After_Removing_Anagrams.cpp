//
// Created by user on 2025/10/13.
//
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
    bool isAnagram(string a, string b){
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        if(a == b){
            return true;
        }else{
            return false;
        }
    }
public:
    vector<string> removeAnagrams(vector<string>& words) {
        if(words.empty()){
            return {};
        }

        vector<string> ans;
        int n = words.size();

        int cur = 0;
        int next = cur+1;

        while (next < n){
            while (isAnagram(words[cur], words[next])){
                next++;
                if(next>=n){
                    break;
                }
            }
            ans.push_back(words[cur]);

            cur = next;
            next++;
        }

        if(ans.empty() || !isAnagram(words[n-1], ans.back())){
            ans.push_back(words[n-1]);
        }

        return ans;
    }
};