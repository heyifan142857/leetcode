//
// Created by user on 2025/9/22.
//
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        int fre = 0;
        int cnt = 0;
        unordered_map<int, int> mp;

        for (auto num: nums) {
            mp[num]++;
            if(mp[num] == fre){
                cnt++;
            }else if(mp[num] > fre){
                fre = mp[num];
                cnt = 1;
            }
        }
        return cnt*fre;
    }
};