// 1855. Maximum Distance Between a Pair of Values
// Created automatically
// Created at 2026-04-19 14:06:46

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        int j = 0;
        int ans = 0;

        for (int i = 0; i < n && j < m; ++i) {
            if (j < i) j = i; // ensure i <= j
            while (j < m && nums1[i] <= nums2[j]) ++j;
            if (j - 1 >= i) ans = max(ans, (j - 1) - i);
        }

        return ans;
    }
};