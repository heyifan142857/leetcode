//
// Created by user on 2025/10/16.
//
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        vector<int> cnt(value, 0);
        for (auto num: nums) {
            cnt[(num % value + value) % value]++;
        }
        int lowest = INT_MAX;
        int lowest_index = -1;
        for (int i = 0; i < value; ++i) {
            if(cnt[i] < lowest){
                lowest = cnt[i];
                lowest_index = i;
            }
        }
        return lowest*value+lowest_index;
    }
};
