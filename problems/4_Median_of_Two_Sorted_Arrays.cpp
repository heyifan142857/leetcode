//
// Created by user on 2025/9/15.
//
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if (m > n) return findMedianSortedArrays(nums2, nums1);

        int left = 0, right = m;
        int halfLen = (m + n + 1) / 2;
        while (left <= right) {
            int i = (left + right) / 2;
            int j = halfLen - i;

            int nums1LeftMax  = (i == 0) ? INT_MIN : nums1[i - 1];
            int nums1RightMin = (i == m) ? INT_MAX : nums1[i];
            int nums2LeftMax  = (j == 0) ? INT_MIN : nums2[j - 1];
            int nums2RightMin = (j == n) ? INT_MAX : nums2[j];

            if (nums1LeftMax <= nums2RightMin && nums2LeftMax <= nums1RightMin) {
                if ((m + n) % 2 == 1) {
                    return max(nums1LeftMax, nums2LeftMax);
                } else {
                    return (max(nums1LeftMax, nums2LeftMax) +
                            min(nums1RightMin, nums2RightMin)) / 2.0;
                }
            } else if (nums1LeftMax > nums2RightMin) {
                right = i - 1;
            } else {
                left = i + 1;
            }
        }
        return 0.0;
    }
};
