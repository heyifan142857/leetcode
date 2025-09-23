//
// Created by user on 2025/9/23.
//
#include <queue>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(), nums.end());
        for (int i = 0; i < k-1; ++i) {
            pq.pop();
        }
        return pq.top();
    }
};