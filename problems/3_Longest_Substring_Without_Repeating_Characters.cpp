//
// Created by user on 2025/8/29.
//

#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int maxLen = 0;
        int curLen = 0;
        unordered_map<char, int> map;
        int left = 0, right = 0;
        while(right < s.size()){
            if(map[s[right]]>0){
                if(curLen > maxLen){
                    maxLen = curLen;
                }
                for (int i = left; i < map[s[right]]; ++i) {
                    map[s[i]] = 0;
                    curLen--;
                    left++;
                }
            }
            map[s[right]] = right+1;
            curLen++;

            right++;
        }
        return max(maxLen, curLen);
    }
};