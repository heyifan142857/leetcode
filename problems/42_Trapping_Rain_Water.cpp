//
// Created by user on 2025/8/28.
//

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> left = height;
        vector<int> right = height;

        for (int i = 1; i < n; ++i) {
            left[i] = max(left[i-1], left[i]);
        }
        for (int i = n-2; i >=0; --i) {
            right[i] = max(right[i], right[i+1]);
        }

        int area = 0;
        for (int i = 0; i < n; ++i) {
            area += (min(left[i], right[i])-height[i]);
        }

        return area;
    }
};

//双指针解法
//class Solution {
//public:
//    int trap(vector<int>& height) {
//        int ans = 0;
//        int left = 0, right = height.size() - 1;
//        int leftMax = 0, rightMax = 0;
//        while (left < right) {
//            leftMax = max(leftMax, height[left]);
//            rightMax = max(rightMax, height[right]);
//            if (height[left] < height[right]) {
//                ans += leftMax - height[left];
//                ++left;
//            } else {
//                ans += rightMax - height[right];
//                --right;
//            }
//        }
//        return ans;
//    }
//};