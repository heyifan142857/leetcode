//
// Created by user on 2025/9/28.
//
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    bool isTriangle(int a, int b, int c){
        return (a+b>c && a+c>b && b+c>a);
    }
public:
    int largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = nums.size() - 1; i >= 2; --i) {
            if (isTriangle(nums[i], nums[i-1], nums[i-2])) {
                return nums[i] + nums[i-1] + nums[i-2];
            }
        }
        return 0;
    }
};