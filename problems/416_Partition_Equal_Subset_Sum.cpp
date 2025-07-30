//
// Created by user on 2025/7/30.
//

#include <vector>
using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int n: nums) {
            sum += n;
        }
        int half = sum / 2;
        if(sum % 2){
            return false;
        }
        vector<bool> available(half+1, false);
        available[0] = true;
        for (int n:nums) {
            for (int i = half; i >= 0; --i) {
                if(available[i] && i + n <= half){
                    if(i+n == half){
                        return true;
                    }
                    available[i+n] = true;
                }
            }
        }
        return false;
    }
};