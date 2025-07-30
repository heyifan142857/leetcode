//
// Created by user on 2025/7/25.
//

#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int maxSum(vector<int>& nums) {
        vector<int> count(201, 0);
        int total = 0;
        int remaining = 0;
        int maxVal = INT_MIN;
        for (int n: nums) {
            maxVal = max(maxVal, n);
            if(!count[n+100] && n > 0){
                total += n;
                remaining++;
            }
            count[n+100]++;
        }

        if(remaining == 0){
            total += maxVal;
        }
        return total;
    }
};